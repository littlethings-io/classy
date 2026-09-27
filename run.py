import os
import shutil
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parent
BUILD_ROOT = ROOT / "build"
APP_BUILD_DIR = BUILD_ROOT / "build-app"
TEST_BUILD_DIR = BUILD_ROOT / "build-tests"
TOOLCHAIN_BIN = ROOT / "compiler" / "mingw64" / "bin"
C_COMPILER = TOOLCHAIN_BIN / "gcc.exe"
CXX_COMPILER = TOOLCHAIN_BIN / "g++.exe"
MAKE_PROGRAM = TOOLCHAIN_BIN / "mingw32-make.exe"
EXTERN_DIR = ROOT / "extern"


def log(message: str) -> None:
    print(f"[RUN] {message}", flush=True)


def tool_environment() -> dict[str, str]:
    environment = os.environ.copy()
    environment["PATH"] = str(TOOLCHAIN_BIN) + os.pathsep + environment.get("PATH", "")
    return environment


def find_cmake() -> Path:
    """Prefer the repository's CMake, with system CMake as a convenience fallback."""
    if EXTERN_DIR.is_dir():
        bundled = sorted(EXTERN_DIR.glob("**/bin/cmake.exe"))
        if bundled:
            return bundled[0]

    system_cmake = shutil.which("cmake")
    if system_cmake:
        log("Bundled CMake executable not found; using CMake from PATH.")
        return Path(system_cmake)

    raise FileNotFoundError(
        "No CMake executable was found. Put the Windows CMake binary package "
        "under extern/ so it contains a bin/cmake.exe file."
    )


def verify_tools() -> None:
    missing = [
        path
        for path in (C_COMPILER, CXX_COMPILER, MAKE_PROGRAM)
        if not path.is_file()
    ]
    if missing:
        names = ", ".join(str(path.relative_to(ROOT)) for path in missing)
        raise FileNotFoundError(f"Missing bundled build tool(s): {names}")


def run_command(command: list[str]) -> None:
    log(" ".join(command))
    subprocess.run(command, cwd=ROOT, env=tool_environment(), check=True)


def configure(build_unit_tests: bool = False) -> tuple[Path, Path]:
    verify_tools()
    cmake = find_cmake()
    build_dir = TEST_BUILD_DIR if build_unit_tests else APP_BUILD_DIR
    run_command(
        [
            str(cmake),
            "-S",
            str(ROOT),
            "-B",
            str(build_dir),
            "-G",
            "MinGW Makefiles",
            "-DCMAKE_BUILD_TYPE=Release",
            "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
            f"-DBUILD_UNIT_TESTS={'ON' if build_unit_tests else 'OFF'}",
            f"-DCMAKE_C_COMPILER={C_COMPILER}",
            f"-DCMAKE_CXX_COMPILER={CXX_COMPILER}",
            f"-DCMAKE_MAKE_PROGRAM={MAKE_PROGRAM}",
        ]
    )
    return cmake, build_dir


def build(build_unit_tests: bool = False) -> tuple[Path, Path]:
    cmake, build_dir = configure(build_unit_tests)
    build_command = [str(cmake), "--build", str(build_dir), "--parallel"]
    if build_unit_tests:
        build_command.extend(["--target", "unit_tests"])
    run_command(build_command)
    return cmake, build_dir


def delete_app_build_folder() -> None:
    if APP_BUILD_DIR.exists():
        shutil.rmtree(APP_BUILD_DIR)
        log("Deleted app build folder.")
    else:
        log("App build folder does not exist.")


def delete_build_folder() -> None:
    if BUILD_ROOT.exists():
        shutil.rmtree(BUILD_ROOT)
        log("Deleted build folder.")
    else:
        log("Build folder does not exist.")


def clean_build() -> None:
    delete_app_build_folder()
    build()


def run_program() -> None:
    executable = APP_BUILD_DIR / "classy.exe"
    if not executable.is_file():
        raise FileNotFoundError("classy.exe was not found. Build the project first.")
    run_command([str(executable)])


def build_and_run() -> None:
    build()
    run_program()


def build_unit_tests() -> tuple[Path, Path]:
    return build(build_unit_tests=True)


def run_all_google_tests() -> None:
    cmake, build_dir = build_unit_tests()
    ctest = cmake.with_name("ctest.exe")
    if not ctest.is_file():
        raise FileNotFoundError(f"CTest was not found beside CMake: {ctest}")
    run_command([str(ctest), "--test-dir", str(build_dir), "--output-on-failure"])


def run_test_target() -> None:
    cmake, build_dir = build_unit_tests()
    run_command([str(cmake), "--build", str(build_dir), "--target", "test"])


ACTIONS = {
    "0": ("Clean build", clean_build),
    "1": ("Build", build),
    "2": ("Build and run", build_and_run),
    "3": ("Run", run_program),
    "4": ("Delete build folder", delete_build_folder),
    "5": ("Run all Google tests", run_all_google_tests),
    "6": ("Run test target", run_test_target),
}


def main() -> int:
    print("[ commands ]")
    for number, (label, _) in ACTIONS.items():
        print(f"{number}. {label}")

    choice = input(">>> Run command: ").strip()
    action = ACTIONS.get(choice)
    if action is None:
        print("Unknown command.", file=sys.stderr)
        return 2

    try:
        action[1]()
    except (FileNotFoundError, subprocess.CalledProcessError) as error:
        print(f"[RUN] ERROR: {error}", file=sys.stderr)
        return 1

    log("Done.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
