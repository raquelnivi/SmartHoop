from ImageConverter import ImageConverter
from PaletteConverter import PaletteConverter
from FileWriter import FileWriter

class Controller():

    IMAGESPATH:str=r"C:\Users\raque\Documents\SmartHoop\Images\TEST"
    PALETTESPATH:str=r"C:\Users\raque\Documents\SmartHoop\Palettes"
    OUTPUTPATH:str=r"C:\Users\raque\Documents\SmartHoop\Arduino\SmartHoop"
    fileWriter:FileWriter
    imageConverter:ImageConverter

    def mainController(self):
        self.fileWriter = FileWriter(self.OUTPUTPATH)
        self.imageConverter = ImageConverter(self.fileWriter, self.IMAGESPATH, self.OUTPUTPATH)
        self.imageConverter.mainConverter()
        self.paletteConverter = PaletteConverter(self.fileWriter, self.PALETTESPATH, self.OUTPUTPATH)
        self.paletteConverter.mainConverter()
