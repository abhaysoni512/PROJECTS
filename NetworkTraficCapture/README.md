# NetworkTraficCapture

## Structure

- `src/` - C++ source and header files
- `bindings/` - pybind11 Python bindings
- `python/` - Python scripts for analysis and plotting
- `tests/` - Unit and integration tests
- `build/` - Build artifacts (should be gitignored)

## Build & Usage

1. Build with CMake (requires libpcap, pybind11)
2. Use Python scripts in `python/` for analysis and visualization

## Notes

- Update CMakeLists.txt and import paths if you move files.
- Add more details as your project evolves.
