#!/bin/bash

OUTPUT="projeto.txt"
> "$OUTPUT"

#######################################
# HEADER FIXO (baixo custo, alto valor)
#######################################
cat <<EOF >> "$OUTPUT"
PROJECT="$(basename "$(pwd -P)")"
PURPOSE: Snapshot of real project code. Names and structure must not be inferred.

EOF

#######################################
# 1. STRUCTURE (árvore completa)
#######################################
echo "STRUCTURE:" >> "$OUTPUT"

if command -v tree >/dev/null 2>&1; then
    tree -I ".*|obj|*.o|*.a|*.out" --noreport >> "$OUTPUT"
else
    find . \
        -not -path "*/.*" \
        -not -path "*/obj/*" \
        -not -name "*.o" \
        | sort >> "$OUTPUT"
fi

echo -e "\nCONTENT:" >> "$OUTPUT"

#######################################
# 2. Função de processamento segura
#######################################
process_file() {
    local file="$1"

    echo "file:${file#./}" >> "$OUTPUT"

    # Compacta linhas vazias consecutivas
    # Mantém comentários e separação lógica
    sed '
        /^[[:space:]]*$/{
            N
            /^\n$/D
        }
    ' "$file" >> "$OUTPUT"

    echo "---" >> "$OUTPUT"
}

#######################################
# 3. Coleta ordenada e robusta
#######################################

# Headers
find . -type f -name "*.h" -not -path "*/.*" | sort |
while IFS= read -r f; do
    process_file "$f"
done

# Makefiles
find . -type f -name "Makefile" -not -path "*/.*" | sort |
while IFS= read -r f; do
    process_file "$f"
done

# main*.c (ponto de entrada)
find . -type f -name "main*.c" -not -path "*/.*" -not -path "*/obj/*" | sort |
while IFS= read -r f; do
    process_file "$f"
done

# Demais .c
find . -type f -name "*.c" \
    -not -name "main*.c" \
    -not -path "*/.*" \
    -not -path "*/obj/*" | sort |
while IFS= read -r f; do
    process_file "$f"
done

echo "✓ Contexto gerado com sucesso em: $OUTPUT"
