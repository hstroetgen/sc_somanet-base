
API
=================

The API for the module_ethernet_dual component is divided into the Server API and Client API.
Server API can be found in ethernet_dual_server.h, whereas the client API is located at ethernet_dual_client.h. 
Including these headers and adding the module_ethernet_smi to your application is enough to access the whole functionality.

Server API
-----------

.. doxygenfunction:: eth_phy_reset
.. doxygenfunction:: ethernet_server_p1
.. doxygenfunction:: ethernet_server_p2
.. doxygenfunction:: fwUpdt_loop
.. doxygenfunction:: ethernetHUB


Client API
------------

.. doxygenfunction:: ethernet_fetcher
.. doxygenfunction:: ethernet_send
