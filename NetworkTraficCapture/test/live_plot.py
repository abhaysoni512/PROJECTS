import packet_capture
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pandas as pd

# === Create 3 Figures ===
fig1, ax1 = plt.subplots()
fig2, ax2 = plt.subplots()
fig3, ax3 = plt.subplots()

bars1 = ax1.bar(["TCP", "UDP", "Other"], [0, 0, 0], color=["skyblue", "orange", "gray"])
bars2 = ax2.bar([], [])
bars3 = ax3.barh([], [])

def update_all(frame):
    # Capture 30 packets per update
    packets = packet_capture.capture_packets(30)
    df = pd.DataFrame([{
        "src_ip": p.src_ip,
        "dst_ip": p.dst_ip,
        "protocol": p.protocol,
        "src_port": p.src_port,
        "dst_port": p.dst_port
    } for p in packets])

    # === Figure 1: Protocol Count ===
    counts = df["protocol"].value_counts()
    tcp = counts.get("TCP", 0)
    udp = counts.get("UDP", 0)
    other = len(df) - tcp - udp
    for bar, val in zip(bars1, [tcp, udp, other]):
        bar.set_height(val)
