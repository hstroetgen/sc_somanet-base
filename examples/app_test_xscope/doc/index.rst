====================
XScope Simple Test
====================

.. contents:: In this document
    :backlinks: none
    :depth: 3

This test show a simple example on the use of XScope

Hardware setup
===============
You need a SOMANET node consisting, at least, on a Core board.

Quick how-to
============

* Configure your Makefile with your SOMANET Core Board. e.g.

::

 TARGET = SOMANET-C22

* In the main.xc, include the board support package for your Core Board. e.g.

::

#include <CORE_C22-rev-a.bsp>

* Enable your Real-Time Mode XScope in your Run Configuration.

* Run!
