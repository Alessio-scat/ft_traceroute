# ft_traceroute

## Project Overview

`ft_traceroute` is a custom implementation of the Unix `traceroute` command in C. This tool helps trace the path that IP packets take from a local machine to a specified destination, showing each hop (router) along the route and the time it takes for the packet to reach each hop. The project focuses on IPv4 and uses UDP packets to simulate network traffic, capturing ICMP responses to map out the route.

## Features

- Sends UDP packets with varying TTL (Time-to-Live) to simulate network hops.
- Receives ICMP "Time Exceeded" messages to identify intermediate routers.
- Displays round-trip times (RTT) for each hop, providing insights into latency.
- Handles multiple responses per hop, allowing for visualization of **load balancing** in the network.
- Stops once it receives an ICMP "Port Unreachable" message from the final destination.

## How It Works

1. The program sends out UDP packets to a destination IP or hostname.
2. For each packet, the TTL is incremented, forcing the packet to expire at each hop (router) along the route.
3. Each intermediate router returns an ICMP "Time Exceeded" message when the TTL expires, allowing `ft_traceroute` to identify the router and measure the RTT.
4. When the packet reaches the destination, an ICMP "Port Unreachable" message is sent, indicating the end of the trace.

## Usage

1. **Compile the program**:
    ```bash
    make
    ```

2. **Run the program**:
    ```bash
    sudo ./ft_traceroute [destination]
    ```

    Example:
    ```bash
    sudo ./ft_traceroute google.com
    ```

    The tool will trace the route to `google.com` and display each hop along the path, including the RTT for each packet.

3. **Help Option**:
    The only implemented option is `--help`, which displays a help message.

    ```bash
    ./ft_traceroute --help
    ```

## Implementation Details

- **Socket Creation**: 
    - A raw UDP socket is used to send the probe packets.
    - A raw ICMP socket listens for ICMP responses from the network.
    
- **TTL Management**: 
    - The TTL (Time-to-Live) value is incremented in each loop, simulating the packet’s journey through each router until it reaches the destination.

- **Load Balancing Handling**: 
    - If multiple responses are received from different routers for the same TTL, all responses are displayed, illustrating network load balancing effects.

- **Error Handling**:
    - The program gracefully handles errors like network failures, incorrect hostnames, and lack of root privileges.

## Known Limitations

- Only IPv4 is supported.
- The program does not perform DNS resolution for intermediate hops.
- Limited to basic UDP probing without advanced flags like in the real `traceroute`.

## Future Enhancements

- Support for additional flags (`-m`, `-p`, etc.) to customize the behavior.
- Add DNS resolution for hop IP addresses.
- Implement support for IPv6.
- Optimize performance by reducing sleep times and improving packet handling.

## Requirements

- Linux-based system with a kernel version ≥ 4.0.
- C compiler (e.g., GCC).
- Root privileges to create raw sockets.

## References

- [Linux Man Page for traceroute](https://man7.org/linux/man-pages/man8/traceroute.8.html)
- [How Traceroute Works - Cisco](https://learningnetwork.cisco.com/s/question/0D53i00000Kt6MsCAJ/how-does-traceroute-work-with-udp-on-packet-level)