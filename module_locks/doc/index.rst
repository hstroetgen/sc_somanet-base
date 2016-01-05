=============================
Lock handling module
=============================

.. contents:: In this document
    :backlinks: none
    :depth: 3

This module provides access to hardware and software locks for use in
concurrent C programs. In general it is not safe to use these to
marshall within XC due to the assumptions XC
makes about safe concurrent data access.

Two types of locks are provided. Hardware locks are fast and power
efficient but there are a limited number per tile. Software locks are
slower but you can use an unlimited number of them.

This module was originally obtained from XMOS public repositories_. 

.. note:: This module is internally used by certain SOMANET Libraries. Just advanced users are recommended to use it. 

Hardware lock API
-----------------

.. doxygentypedef:: hwlock_t

.. doxygenfunction:: hwlock_alloc
.. doxygenfunction:: hwlock_free
.. doxygenfunction:: hwlock_acquire
.. doxygenfunction:: hwlock_release

Software lock API
-----------------

.. doxygentypedef:: swlock_t

.. doxygendefine:: SWLOCK_INITIAL_VALUE

.. doxygenfunction:: swlock_init
.. doxygenfunction:: swlock_try_acquire
.. doxygenfunction:: swlock_acquire
.. doxygenfunction:: swlock_release


.. _XMOS public repositories: https://github.com/xcore/sc_util/tree/c06706f4b71dfa966f4a5a4d0d76d7188214db3f/module_locks
