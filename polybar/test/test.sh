#!/bin/bash
ETH="$(ip link show | grep "enp" | cut -d " " -f 6)"
echo "$ETH"
