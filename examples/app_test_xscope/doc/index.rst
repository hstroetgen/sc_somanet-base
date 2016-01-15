====================
XScope Simple Test
====================

.. contents:: In this document
    :backlinks: none
    :depth: 3

This test shows a simple example on the use of XScope.
While running, it should display a sinusoidal wave over XScope.

This app was originall provided by XMOS as an `Application Note`_.

.. cssclass:: github

  `See Application on Public Repository <https://github.com/synapticon/sc_somanet-base/tree/master/examples/app_test_xscope>`_

Hardware setup
===============

You need a SOMANET node consisting, at least, on a SOMANET Core board.

Quick how-to
============

1. Configure your Makefile with your SOMANET Core Board. e.g.

	::

		TARGET = SOMANET-C22

2. In the main.xc, include the board support package for your Core Board. e.g.

	::

		#include <CORE_C22-rev-a.bsp>

3. Enable your Real-Time Mode XScope in your Run Configuration.

4. Run!

.. _`Application Note`: https://www.xmos.com/download/private/AN00196%3A-Getting-Started-with-Real-Time-xSCOPE-in-xTIMEcomposer-Studio%281.0.0rc1%29.pdf
