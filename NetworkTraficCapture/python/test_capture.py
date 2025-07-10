# test/test_capture.py
import packet_capture

packets = packet_capture.capture_packets(5)
for p in packets:
    print(f"{p.protocol}: {p.src_ip}:{p.src_port} → {p.dst_ip}:{p.dst_port}")
