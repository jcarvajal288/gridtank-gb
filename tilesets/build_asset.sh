#!/usr/bin/env bash

set -e

P2A="/var/home/max/Programs/GameBoyDev/gbdk/bin/png2asset"

usage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  --tileset <tileset.png>    Generate the standalone tileset (.c/.h) or use as reference"
    echo "  --map <map.png>            Generate the map array (.c/.h)"
    echo "  --map-dir <directory>      Generate map arrays for all .png files in the input directory"
    echo "  --sprite <sprite.png>      Generate sprite asset (.c/.h) [defaults to -sw 16 -sh 16 -spr8x16 -noflip]"
    echo "  --output-dir <directory>   Output directory for generation results"
    echo "  --sw <width>               Override default sprite width (default: 16)"
    echo "  --sh <height>              Override default sprite height (default: 16)"
    echo "  --no-spr8x16               Disable default 8x16 sprite mode"
    echo "  -h, --help                 Show this help message"
    echo ""
    echo "Note: If --tileset is omitted, png2asset will run in standard map mode without a reference tileset."
    exit 1
}

if [ "$#" -eq 0 ]; then
    usage
fi

TILESET_PNG=""
MAP_PNG=""
MAP_DIR_IN=""
SPRITE_PNG=""
OUTPUT_DIR=""

# Default implied sprite configurations
SPRITE_WIDTH="16"
SPRITE_HEIGHT="16"
SPR8X16="true"

# Parse command line arguments
while [[ "$#" -gt 0 ]]; do
    case $1 in
        --tileset)
            if [ -z "$2" ] || [[ "$2" == --* ]]; then
                echo "Error: --tileset requires a file path argument."
                exit 1
            fi
            TILESET_PNG="$2"
            shift 2
            ;;
        --map)
            if [ -z "$2" ] || [[ "$2" == --* ]]; then
                echo "Error: --map requires a file path argument."
                exit 1
            fi
            MAP_PNG="$2"
            shift 2
            ;;
        --map-dir)
            if [ -z "$2" ] || [[ "$2" == --* ]]; then
                echo "Error: --map-dir requires a directory path argument."
                exit 1
            fi
            MAP_DIR_IN="$2"
            shift 2
            ;;
        --sprite)
            if [ -z "$2" ] || [[ "$2" == --* ]]; then
                echo "Error: --sprite requires a file path argument."
                exit 1
            fi
            SPRITE_PNG="$2"
            shift 2
            ;;
        --output-dir)
            if [ -z "$2" ] || [[ "$2" == --* ]]; then
                echo "Error: --output-dir requires a directory path argument."
                exit 1
            fi
            OUTPUT_DIR="$2"
            shift 2
            ;;
        --sw)
            if [ -z "$2" ] || [[ "$2" == --* ]]; then
                echo "Error: --sw requires a width value."
                exit 1
            fi
            SPRITE_WIDTH="$2"
            shift 2
            ;;
        --sh)
            if [ -z "$2" ] || [[ "$2" == --* ]]; then
                echo "Error: --sh requires a height value."
                exit 1
            fi
            SPRITE_HEIGHT="$2"
            shift 2
            ;;
        --no-spr8x16)
            SPR8X16="false"
            shift 1
            ;;
        -h|--help)
            usage
            ;;
        *)
            echo "Unknown argument: $1"
            usage
            ;;
    esac
done

# --- Execution Logic ---

# Handle Standalone Tileset Generation
if [ -n "$TILESET_PNG" ]; then
    if [ ! -f "$TILESET_PNG" ]; then
        echo "Error: Tileset file '$TILESET_PNG' does not exist."
        exit 1
    fi

    if [ -z "$MAP_DIR_IN" ] || [ -n "$MAP_PNG" ]; then
        TILESET_DIR=$(dirname "$TILESET_PNG")
        TILESET_BASE=$(basename "$TILESET_PNG" .png)
        TILESET_OUT="${TILESET_DIR}/${TILESET_BASE}"

        echo "Step 1: Generating tileset from '${TILESET_PNG}'..."
        $P2A "$TILESET_PNG" -map -tiles_only -noflip -c "${TILESET_OUT}.c"
    fi
fi

# Handle Single Map Generation
if [ -n "$MAP_PNG" ]; then
    if [ ! -f "$MAP_PNG" ]; then
        echo "Error: Map file '$MAP_PNG' does not exist."
        exit 1
    fi

    if [ -n "$OUTPUT_DIR" ]; then
        mkdir -p "$OUTPUT_DIR"
        MAP_OUT_DIR="$OUTPUT_DIR"
    else
        MAP_OUT_DIR=$(dirname "$MAP_PNG")
    fi

    MAP_BASE=$(basename "$MAP_PNG" .png)
    MAP_OUT="${MAP_OUT_DIR}/${MAP_BASE}"

    if [ -n "$TILESET_PNG" ]; then
        echo "Step 2: Generating map array from '${MAP_PNG}' using reference tileset '${TILESET_PNG}'..."
        $P2A "$MAP_PNG" -map -source_tileset "$TILESET_PNG" -maps_only -noflip -c "${MAP_OUT}.c"
    else
        echo "Step 2: Generating standalone map from '${MAP_PNG}'..."
        $P2A "$MAP_PNG" -map -noflip -c "${MAP_OUT}.c"
    fi
fi

# Handle Directory Map Generation
if [ -n "$MAP_DIR_IN" ]; then
    if [ ! -d "$MAP_DIR_IN" ]; then
        echo "Error: Map directory '$MAP_DIR_IN' does not exist."
        exit 1
    fi

    OUT_DIR="${OUTPUT_DIR:-$MAP_DIR_IN}"
    mkdir -p "$OUT_DIR"

    echo "Step 3: Processing all PNG maps in '${MAP_DIR_IN}'..."

    shopt -s nullglob
    PNG_FILES=("${MAP_DIR_IN}"/*.png)
    shopt -u nullglob

    if [ ${#PNG_FILES[@]} -eq 0 ]; then
        echo "Warning: No .png files found in '${MAP_DIR_IN}'."
    else
        for img in "${PNG_FILES[@]}"; do
            if [ -n "$TILESET_PNG" ]; then
                REAL_IMG=$(readlink -f "$img" 2>/dev/null || realpath "$img")
                REAL_TILESET=$(readlink -f "$TILESET_PNG" 2>/dev/null || realpath "$TILESET_PNG")
                
                if [ "$REAL_IMG" == "$REAL_TILESET" ]; then
                    continue
                fi
            fi

            MAP_BASE=$(basename "$img" .png)
            MAP_OUT="${OUT_DIR}/${MAP_BASE}"

            echo "  -> Generating map for '${img}'..."
            if [ -n "$TILESET_PNG" ]; then
                $P2A "$img" -map -source_tileset "$TILESET_PNG" -maps_only -noflip -c "${MAP_OUT}.c"
            else
                $P2A "$img" -map -noflip -c "${MAP_OUT}.c"
            fi
        done
    fi
fi

# Handle Sprite Generation
if [ -n "$SPRITE_PNG" ]; then
    if [ ! -f "$SPRITE_PNG" ]; then
        echo "Error: Sprite file '$SPRITE_PNG' does not exist."
        exit 1
    fi

    if [ -n "$OUTPUT_DIR" ]; then
        mkdir -p "$OUTPUT_DIR"
        SPRITE_OUT_DIR="$OUTPUT_DIR"
    else
        SPRITE_OUT_DIR=$(dirname "$SPRITE_PNG")
    fi

    SPRITE_BASE=$(basename "$SPRITE_PNG" .png)
    SPRITE_OUT="${SPRITE_OUT_DIR}/${SPRITE_BASE}"

    # Build argument array with implied defaults including -noflip
    P2A_ARGS=("$SPRITE_PNG" -sw "$SPRITE_WIDTH" -sh "$SPRITE_HEIGHT" -noflip)
    if [ "$SPR8X16" = "true" ]; then
        P2A_ARGS+=("-spr8x16")
    fi
    P2A_ARGS+=("-c" "${SPRITE_OUT}.c")

    echo "Generating sprite asset from '${SPRITE_PNG}' (sw: $SPRITE_WIDTH, sh: $SPRITE_HEIGHT, 8x16: $SPR8X16, noflip: true)..."
    $P2A "${P2A_ARGS[@]}"
fi

echo "Done!"