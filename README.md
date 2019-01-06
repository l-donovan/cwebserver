# **cwebserver** by [l-donovan](https://www.github.com/l-donovan "Luke Donovan")
Just run `make` to create the library

Optionally run `make demo` to compile the demo server `bin/demo`

To start the server, run `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/libcwebserver.so bin/demo`

`cwsclient.js` and `cwsclient.html` were thrown together for testing purposes. Something like `curl -X GET 'http://localhost:<port>'` would work just as well
