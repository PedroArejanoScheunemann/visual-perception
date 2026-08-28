## Architecture

The project follows a modular architecture where each component has a clearly defined responsibility and communicates through well-defined interfaces.

The main design goal is to keep pipeline orchestration, model-specific processing, inference execution, perception outputs, and result visualization independent. This allows the system to evolve without requiring changes across unrelated components when new capabilities are introduced.

For this purpose, responsibilities are separated across different layers of the perception pipeline:

- **Engine** — orchestrates the perception pipeline and manages registered models.
- **Models** — implement perception algorithms and define their processing pipelines.
- **Backends** — provide the underlying inference runtime implementations.
- **Perception State** — stores and exposes the outputs generated during perception processing.
- **Visualizers** — provide utilities for rendering and inspecting perception outputs.
