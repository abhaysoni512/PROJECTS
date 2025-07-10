import packet_capture
import pandas as pd
import matplotlib.pyplot as plt

packets = packet_capture.capture_packets(100)

data = [{
    "src_ip": p.src_ip,
    "dst_ip": p.dst_ip,
    "protocol": p.protocol,
    "src_port": p.src_port,
    "dst_port": p.dst_port
} for p in packets]

df = pd.DataFrame(data)

# 1. Protocol Distribution Pie Chart
plt.figure(1)
protocol_counts = df["protocol"].value_counts()
plt.pie(protocol_counts, labels=protocol_counts.index, autopct='%1.1f%%', startangle=140)
plt.title("Protocol Distribution")
plt.axis('equal')

# 2. Top Source IPs
plt.figure(2)
top_src_ips = df["src_ip"].value_counts().head(5)
top_src_ips.plot(kind='bar', color='skyblue')
plt.title("Top 5 Source IPs")
plt.xlabel("IP Address")
plt.ylabel("Packet Count")
plt.xticks(rotation=45)

# 3. Top Destination Ports
plt.figure(3)
top_dst_ports = df["dst_port"].value_counts().head(5)
top_dst_ports.plot(kind='barh', color='salmon')
plt.title("Top 5 Destination Ports")
plt.xlabel("Packet Count")
plt.ylabel("Port Number")

#  Show all at once (non-blocking)
plt.show(block=False)
plt.pause(100)  # show for 10 seconds
plt.close('all')  # or keep them open for interaction
