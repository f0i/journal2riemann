#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <systemd/sd-journal.h>
#include <riemann/riemann-client.h>
#include <riemann/simple.h>

#define min(a,b) (a < b ? a : b)

#define NOMATCH -1
#define MATCHNOTHING 0
#define MATCH(matchtype,matchval,typename,name) \
  if( matched == NOMATCH && \
      strncmp(field,name,min(sizeof(name)-1,len)) == 0) { \
    type = typename; \
    matchtype matchval; \
    field = field + sizeof(name) - 1; \
    len = len - (sizeof(name) - 1); \
  }  
#define A matched = ATTRIBUTE; attr = 
#define F matched = 
#define T matched = TAG; attr = 

enum RiemannType { STRING=100, STATE, TIME, SERVICEPART, ATTRIBUTE, TAG };

#define MAX_DATA 1000000
static char valuebuf[MAX_DATA];
static char servicename[MAX_DATA*2];

static char* states[] = {"emerg", "alert", "critical", "error", "warning", "notice", "info", "debug"};

int main(int argc, char** argv){
  int r;
  char* end;
  sd_journal *j;
  riemann_client_t *c;
  riemann_message_t *req, *res;
  riemann_event_t *event;

  r = sd_journal_open(&j, SD_JOURNAL_LOCAL_ONLY | SD_JOURNAL_SYSTEM);
  assert(r == 0);
  
  if(argc != 3){
    fprintf(stderr,"usage: journal2riemann 127.0.0.1 5555\n"); 
    exit(1);
  }
  long port = strtol(argv[2],&end,10);
  c = riemann_client_create (RIEMANN_CLIENT_TCP, argv[1], port);

  r = sd_journal_seek_tail(j);
  assert(r == 0);
  for (;;)  {
    const void *field; size_t len;
    r = sd_journal_next(j); assert (r >= 0);
    if (r == 0) { 
      r = sd_journal_wait(j, (uint64_t) -1); 
      assert (r >= 0); continue; 
    }
    
    event = riemann_event_create(RIEMANN_EVENT_FIELD_NONE);
    strncpy(servicename,"journal",8);

    SD_JOURNAL_FOREACH_DATA(j, field, len){
      char* attr = ""; enum RiemannType type; void* val;

      int matched = NOMATCH;
      MATCH(F,RIEMANN_EVENT_FIELD_DESCRIPTION      , STRING             , "MESSAGE=")
      MATCH(A,"message_id"                         , STRING             , "MESSAGE_ID=")
      MATCH(F,RIEMANN_EVENT_FIELD_STATE            , STATE              , "PRIORITY=")
      MATCH(F,MATCHNOTHING                         , STRING             , "CODE_FILE=")
      MATCH(F,MATCHNOTHING                         , STRING             , "CODE_LINE=")
      MATCH(F,MATCHNOTHING                         , STRING             , "CODE_FUNC=")
      MATCH(F,MATCHNOTHING                         , STRING             , "ERRNO=")
      MATCH(F,MATCHNOTHING                         , STRING             , "SYSLOG_FACILITY=")
      MATCH(F,MATCHNOTHING                         , STRING             , "SYSLOG_IDENTIFIER=")
      MATCH(F,MATCHNOTHING                         , STRING             , "SYSLOG_PID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_PID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_UID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_GID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_COMM=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_EXE=")
      MATCH(A,"command_line"                       , STRING             , "_CMDLINE=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_CAP_EFFECTIVE=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_AUDIT_SESSION=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_AUDIT_LOGINUID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_SYSTEMD_CGROUP=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_SYSTEMD_SESSION=")
      MATCH(F,SERVICEPART                          , STRING             , "_SYSTEMD_UNIT=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_SYSTEMD_USER_UNIT=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_SYSTEMD_OWNER_UID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_SYSTEMD_SLICE=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_SELINUX_CONTEXT=")
      MATCH(F,RIEMANN_EVENT_FIELD_TIME             , TIME               , "_SOURCE_REALTIME_TIMESTAMP=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_BOOT_ID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_MACHINE_ID=")
      MATCH(F,RIEMANN_EVENT_FIELD_HOST             , STRING             , "_HOSTNAME=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_TRANSPORT=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_KERNEL_DEVICE=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_KERNEL_SUBSYSTEM=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_UDEV_SYSNAME=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_UDEV_DEVNODE=")
      MATCH(F,MATCHNOTHING                         , STRING             , "_UDEV_DEVLINK=")
      MATCH(F,MATCHNOTHING                         , STRING             , "COREDUMP_UNIT=")
      MATCH(F,MATCHNOTHING                         , STRING             , "COREDUMP_USER_UNIT=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_UID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_GID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_COMM=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_EXE=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_CMDLINE=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_AUDIT_SESSION=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_AUDIT_LOGINUID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_SYSTEMD_CGROUP=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_SYSTEMD_SESSION=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_SYSTEMD_OWNER_UID=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_SYSTEMD_UNIT=")
      MATCH(F,MATCHNOTHING                         , STRING             , "OBJECT_SYSTEMD_USER_UNIT=")
      MATCH(F,MATCHNOTHING                         , STRING             , "__CURSOR=")
      MATCH(F,MATCHNOTHING                         , STRING             , "__REALTIME_TIMESTAMP=")
      MATCH(F,MATCHNOTHING                         , STRING             , "__MONOTONIC_TIMESTAMP=") 
      
      if(matched != MATCHNOTHING && matched != NOMATCH){
        memcpy(valuebuf,field,len); *(valuebuf+len) = 0;
        switch(type){
          case STATE:
            val = (void*) states[atoi(valuebuf)];
            break;
          case TIME:
            *(valuebuf+len-6) = 0;
            long t = strtol(valuebuf,&end,10);
            val = (int64_t) t;
            break;
          default:
            val = (void*) valuebuf;      
        }
        
        switch(matched){
          case ATTRIBUTE:
            riemann_event_string_attribute_add(event,attr,valuebuf); break;
          case TAG:
            riemann_event_tag_add(event,valuebuf); break;
          case SERVICEPART: 
            if(len > 0){
              strncat(servicename," ",2);
              strncat(servicename,valuebuf,len+1);
            }
            break;
          default:
            riemann_event_set(event,matched,val,RIEMANN_EVENT_FIELD_NONE);
        }
      }
    } 
    riemann_event_set(event,RIEMANN_EVENT_FIELD_SERVICE,servicename,RIEMANN_EVENT_FIELD_NONE);
    req = riemann_message_create_with_events(event, NULL);
    res = riemann_communicate(c, req);
    if (!res)
    {
      fprintf (stderr, "Error communicating with Riemann: %s\n",
               strerror (errno));
      exit (1);
    }

    if (res->error)
    {
      fprintf (stderr, "Error communicating with Riemann: %s\n",
               res->error);
      exit (1);
    }

    if (res->has_ok && !res->ok)
    {
      fprintf (stderr, "Error communicating with Riemann: %s\n",
               strerror (errno));
      exit (1);
    }
    riemann_message_free(res); 
  }
  sd_journal_close(j);
  riemann_client_free (c);
  return 0;
}
