# README

Clone the repo to RIOT/examples and run `make` to compile. From the directory,
setup network device with `../../dist/tools/tapsetup/tapsetup -c`.  
Start the server with `tap0` and use `echo "hello" | nc -u6 ff02::1%tap0 12345`
to send UDP packet to the interface.
