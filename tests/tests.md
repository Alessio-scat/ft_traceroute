
# Test Cases for ft_traceroute

## 1. Basic Localhost Test
```bash
sudo ./ft_traceroute 127.0.0.1
```

## 2. Trace to a Public Domain (e.g., Google)
```bash
sudo ./ft_traceroute google.com
```

## 3. Invalid Hostname Handling
```bash
sudo ./ft_traceroute invalidhostname
```

## 4. Network Load Balancing Test
```bash
sudo ./ft_traceroute cloudflare.com
```

## 5. Max Hops Limit Test
```bash
sudo ./ft_traceroute akamai.com
```

## 6. Non-Responsive Node Handling
```bash
sudo ./ft_traceroute firewalledaddress
```

## 7. ICMP Rate-Limited Target
```bash
sudo ./ft_traceroute facebook.com
```

## 8. High Latency Test
```bash
sudo ./ft_traceroute japan.com
```

## 9. Help Flag Test
```bash
./ft_traceroute --help
```
