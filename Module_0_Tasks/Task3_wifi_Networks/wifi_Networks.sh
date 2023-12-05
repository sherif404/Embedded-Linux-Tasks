#!/bin/bash

# List available WiFi networks with SSID and signal strengths
network_list=$(nmcli -f SSID,SIGNAL dev wifi | awk 'NR>1 && $1 != "--" {print $1 "," int($2)}')

# Check if there's any visible network to  use .. or print can't recommend any wifii network. 
if [ -z "$network_list" ]; then
    echo "Can't recommend any WiFi network: No visible WiFi networks found."
    exit 0
fi

# Sort networks >> descending order
sorted_networks=$(echo "$network_list" | sort -t',' -k2,2nr)

# the highest signal strength
highest_network=$(echo "$sorted_networks" | head -n 1 | cut -d',' -f1)

# here i check again if the highest signal network is not named   >>in the first check i used "awk" option 
if [ "$highest_network" == "--" ]; then
   echo "Can't recommend any WiFi network: All available networks are hidden."
else
    echo "Available WiFi Networks:"
    echo "------------------------"
    echo "Network Name | Strength"

    while IFS=',' read -r network strength; do
        echo "$network | $strength%"
    done <<< "$sorted_networks"

    echo ""
    echo "Recommendation: Connect to $highest_network"
fi
