# INTRODUCTION
raystack is a fast and a small independent implementation of the TCP/IP protocol suite.

The focus of the raystack TCP/IP implement is to reduce the RAM usage and support to use in DPDK, ROS and many embedded systems.

# FEATURES
* IP (Internet Protocol) including packet forwarding over multiple network interfaces
* ICMP (Internet Group Management Protocol) for network maintenance and debugging
* IGMP (Internet Group Management Protocol) for multicast traffic management
* UDP (User Datagram Protocol) including experimental UDP-lite extensions
* TCP (Transmission Control Protocol) with congestion control, RTT estimation and fast recovery/fast retransmit
* DNS (Domain names resolver)
* DHCP (Dynamic Host Configuration Protocol)
* AUTOIP (for IPv4, conform with RFC 3927)
* ARP (Address Resolution Protocol) for Ethernet
* Berkeley-like socket API

# LICENSE
raystack can be freely used under a BSD license.

# DOCUMENTATION
raystack/doc
