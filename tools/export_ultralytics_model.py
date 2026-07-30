#!/usr/bin/env python3

"""
Exports an Ultralytics model to a deployment format.

Usage:
    python tools/export_ultralytics_model.py [model] [--format FORMAT]

If no model is specified, 'yolo11n' is exported.
If no format is specified, 'onnx' is used.

Examples:
    python tools/export_ultralytics_model.py
    python tools/export_ultralytics_model.py yolo11s
    python tools/export_ultralytics_model.py yolo11n --format coreml
    python tools/export_ultralytics_model.py rtdetr-l --format onnx

The exported model is stored in:

    assets/weights/object/

Any model and export format supported by the installed version of the
Ultralytics package may be used.

See:
    https://docs.ultralytics.com/models/
    https://docs.ultralytics.com/modes/export/
"""

from __future__ import annotations

import argparse
import shutil
from pathlib import Path

from ultralytics import YOLO

DEFAULT_MODEL = "yolo11n"
DEFAULT_FORMAT = "onnx"


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Export an Ultralytics model."
    )

    parser.add_argument(
        "model",
        nargs="?",
        default=DEFAULT_MODEL,
        help=f"Model name (default: {DEFAULT_MODEL})",
    )

    parser.add_argument(
        "--format",
        metavar="FORMAT",
        default=DEFAULT_FORMAT,
        help=f"Export format (default: {DEFAULT_FORMAT})",
    )

    return parser.parse_args()


def get_export_arguments(export_format: str) -> dict:
    arguments = {
        "format": export_format,
    }

    match export_format:
        case "onnx":
            arguments.update(
                simplify=True,
                opset=17,
            )

        case "coreml":
            # Add CoreML-specific options here when needed.
            pass

        case _:
            pass

    return arguments


def get_output_directory(project_root: Path) -> Path:
    return (
        project_root
        / "assets"
        / "weights"
        / "object"
    )


def cleanup_weights(model_name: str) -> None:
    weights = Path(f"{model_name}.pt")

    if weights.exists():
        weights.unlink()


def export_model(
    model_name: str,
    export_format: str,
) -> Path:
    project_root = Path(__file__).resolve().parent.parent

    output_directory = get_output_directory(project_root)

    output_directory.mkdir(parents=True, exist_ok=True)

    print(f"Model : {model_name}")
    print(f"Format: {export_format}")
    print(f"Output: {output_directory}")
    print()

    model = YOLO(f"{model_name}.pt")

    exported_model = Path(
        model.export(
            **get_export_arguments(export_format)
        )
    )

    destination = output_directory / exported_model.name

    shutil.move(exported_model, destination)

    cleanup_weights(model_name)

    return destination


def main() -> int:
    arguments = parse_arguments()

    exported_model = export_model(
        model_name=arguments.model,
        export_format=arguments.format,
    )

    print()
    print("Export completed successfully.")
    print(f"Output: {exported_model}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
