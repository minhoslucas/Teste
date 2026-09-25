import struct
import csv

fmt = 'e'
row_size = struct.calcsize(fmt)

with open("solnascente-3d/data/prestack/by_il/2/samples", "rb") as f, open('samples_2.csv', mode='w', newline='') as h:
    escritor = csv.writer(h)

    while True:
        data = f.read(row_size)
        if not data:
            break
        if len(data) != row_size:
            raise ValueError(f"Partial record read: expected {row_size} bytes, got {len(data)} bytes")
        escritor.writerow(struct.unpack(fmt, data))

print("CSV export finished successfully.")

