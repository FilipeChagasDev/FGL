from fontTools.ttLib import TTFont
font = TTFont('Roboto-Regular.ttf')
cmap = font.getBestCmap()
glyph = font.getGlyphSet()
print(cmap)

for c in cmap:
    if c in glyph:
        print(glyph[c])