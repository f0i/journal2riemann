# Transfer journal logs to Riemann

This is a C client for journal (systemd) which connects to the
[Riemann][riemann] monitoring system in order to convert all Journal logs into
Riemann events.

## Installation

    $ git clone git://github.com/awetzel/journal2riemann
    $ cd journal2riemann
    $ autoreconf -i
    $ ./configure && make && make install

## Usage

In order to forward local logs to Riemann TCP socket listening on localhost:5555

    $ journal2riemann localhost 5555

To use TLS encryption add the CA, CERT and KEY-files as additional parameter

    $ journal2riemann riemann.example.com 5555 ca.crt client.crt client.pem
