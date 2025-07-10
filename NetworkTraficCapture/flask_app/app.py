from flask import Flask, render_template, jsonify
import random
from collections import Counter
import sys
sys.path.append('..')
try:
    import packet_capture
except ImportError:
    packet_capture = None

app = Flask(__name__)

def get_packet_data():
    if packet_capture:
        # Capture 100 packets in real time using your C++/pybind11 module
        packets = packet_capture.capture_packets(100)
        return [
            {"src_ip": p.src_ip, "dst_port": p.dst_port, "protocol": p.protocol}
            for p in packets
        ]
    else:
        # Fallback to dummy data if module not available
        return [
            {"src_ip": random.choice(["192.168.0.101", "192.168.117.171", "20.50.88.233", "192.168.0.1", "13.89.179.10"]),
             "dst_port": random.choice([443, 53, 55502, 55503, 55504]),
             "protocol": random.choice(["TCP", "UDP"])}
            for _ in range(100)
        ]

def get_dashboard_data():
    packets = get_packet_data()
    # Protocol distribution
    protocol_counts = Counter(p["protocol"] for p in packets)
    # Top 5 source IPs
    src_ip_counts = Counter(p["src_ip"] for p in packets).most_common(5)
    # Top 5 destination ports
    dst_port_counts = Counter(str(p["dst_port"]) for p in packets).most_common(5)
    return {
        "protocol_distribution": dict(protocol_counts),
        "top_src_ips": {
            "labels": [ip for ip, _ in src_ip_counts],
            "counts": [count for _, count in src_ip_counts]
        },
        "top_dst_ports": {
            "labels": [port for port, _ in dst_port_counts],
            "counts": [count for _, count in dst_port_counts]
        }
    }

@app.route("/")
def dashboard():
    return render_template("dashboard.html")

@app.route("/api/dashboard")
def api_dashboard():
    return jsonify(get_dashboard_data())

if __name__ == "__main__":
    app.run(debug=True)
