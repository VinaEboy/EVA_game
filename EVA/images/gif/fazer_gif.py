from PIL import Image
import os

#nome do arquivo sem a extensão .png
nome = input()

# Caminho da imagem
current_dir = os.getcwd()
sprite_sheet_path = os.path.join(current_dir, nome + ".png")  # substitua pelo nome real
sprite_sheet = Image.open(sprite_sheet_path)

# Dimensões da imagem
sheet_width, sheet_height = sprite_sheet.size
frame_width = 256
frame_height = 256

# Número de frames na horizontal e vertical
cols = sheet_width // frame_width
rows = sheet_height // frame_height

# Gerar todos os frames na ordem da esquerda pra direita, de cima pra baixo
frames = []
for row in range(rows):
    for col in range(cols):
        x = col * frame_width
        y = row * frame_height
        frame = sprite_sheet.crop((x, y, x + frame_width, y + frame_height))
        frames.append(frame)

# Salvar o GIF animado
gif_path = os.path.join(current_dir, nome + ".gif")
frames[0].save(
    gif_path,
    save_all=True,
    append_images=frames[1:],
    duration=133,
    loop=0,
    disposal=2
)

print(f"GIF com {len(frames)} frames salvo em: {gif_path}")