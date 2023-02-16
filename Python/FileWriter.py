import os

class FileWriter():

    OUTPUTPATH:str
    paletteIncludes:list=[]
    paletteNames:list=[]

    def __init__(self, OUTPUTPATH):
        self.OUTPUTPATH = OUTPUTPATH

    def generateIncludes(self, includeNames, subpath, libraryName):
        includes = ["#ifndef {}_H_\n#define {}_H_\n\n".format(libraryName, libraryName)]
        for includeName in includeNames:
            includePath = os.path.join(subpath, includeName)
            includes.append('#include "{}"\n'.format(includePath))
        return includes

    def writeImagesFile(self, imageNames):
        MIDDLE:str="\nconst uint8_t* const images[] PROGMEM {\n"
        ENDING:str="\n};\n\n#define NUM_IMAGES (sizeof(images) / sizeof(images[0]))\n\n#endif"        
        includes = self.generateIncludes(imageNames, "images", "IMAGES")
        fileText = includes + [MIDDLE] + ["\t{},\n".format(imageName[:-2]) for imageName in imageNames[:-1]] + ["\t{}".format(imageNames[-1][:-2])] 
        fileText = fileText + [ENDING]
        with open(os.path.join(self.OUTPUTPATH, "Images.h"), "w+") as fileToWrite:
            fileToWrite.writelines(fileText)

    def writePalettesFile(self, paletteNames, palettesData):
        MIDDLE:str="const CRGBPalette16 palettes[] PROGMEM = {\n"
        ENDING:str="\n};\n\nconst CRGB colors[] PROGMEM = {\n  CRGB::White, CRGB::Red, CRGB::Purple, CRGB::Blue, CRGB::Green,\n  CRGB::Yellow, CRGB::Orange, CRGB::Pink, CRGB::Teal,\n  CRGB::Magenta, CRGB::LimeGreen, CRGB::HotPink, CRGB::SeaGreen\n};\n\n#define NUM_PALETTES (sizeof(palettes) / sizeof(palettes[0]))\n#define NUM_COLORS (sizeof(colors) / sizeof(colors[0]))\n\n#endif"
        includes = self.generateIncludes([], "", "PALETTESANDCOLORS")
        fileText = includes + palettesData + [MIDDLE] + ["\t{},\n".format(paletteName[:-4]) for paletteName in paletteNames[:-1]] + ["\t{}".format(paletteNames[-1][:-4])] 
        fileText = fileText + [ENDING]
        with open(os.path.join(self.OUTPUTPATH, "PalettesAndColors.h"), "w+") as fileToWrite:
            fileToWrite.writelines(fileText)            