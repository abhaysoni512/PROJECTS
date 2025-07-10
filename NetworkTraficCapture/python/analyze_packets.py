import packet_capture
import pandas as pd

# Capture N packets
N = 50
packets = packet_capture.capture_packets(N)

# Convert to list of dictionaries
data = [{
    "src_ip": p.src_ip,
    "dst_ip": p.dst_ip,
    "protocol": p.protocol,
    "src_port": p.src_port,
    "dst_port": p.dst_port
} for p in packets]

# Convert to DataFrame
df = pd.DataFrame(data)

print("📦 Total Packets Captured:", len(df))

# --- Analysis ---

# 1. Protocol distribution
print("\n🧪 Protocol Distribution:")
print(df["protocol"].value_counts())

# 2. Top source IPs
print("\n🌐 Top 5 Source IPs:")
print(df["src_ip"].value_counts().head())

# 3. Top destination IPs
print("\n🎯 Top 5 Destination IPs:")
print(df["dst_ip"].value_counts().head())

# 4. Top source ports
print("\n🔌 Top 5 Source Ports:")
print(df["src_port"].value_counts().head())

# 5. Top destination ports
print("\n🚪 Top 5 Destination Ports:")
print(df["dst_port"].value_counts().head())
