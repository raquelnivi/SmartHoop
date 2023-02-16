import re, os

class PaletteConverter():
    INPUTPATH:str
    OUTPUTPATH:str

    def __init__(self, fileWriter, INPUTPATH, OUTPUTPATH):
        self.fileWriter = fileWriter
        self.INPUTPATH = INPUTPATH
        self.OUTPUTPATH = OUTPUTPATH

    def extractDataFromFile(self, fileText):
        fileText = fileText.split("0deg,\n")[1]
        fileText = fileText.split(");")[0]
        fileText = fileText.replace("100.000%", "NUM_LEDS")
        fileText = fileText.replace("rgb(", "")
        return fileText

    def cleanRow(self, row):
        if("NUM_LEDS" in row):
            cleanRow = row.replace(")", ",")
            return cleanRow
        else:
            cleanRow = row.split(".")[0]
            cleanRowStart = cleanRow.split(")")[0]
            cleanRowEnd = cleanRow.split(")")[1].strip()
            cleanRow = "{},\tint({}*NUM_LEDS/100),\n".format(cleanRowStart, cleanRowEnd)
            return cleanRow

    def cleanFirstRow(self, firstRow):
        firstRow = firstRow.replace(".000", ",\n")
        firstRow = firstRow.replace(")", ",")        
        return firstRow

    def dropDuplicates(self, fileData):
        cleanData = []
        for row in fileData.split("%,\n"):
            if(cleanData):
                nextRow = self.cleanRow(row)
                if(nextRow.split(",")[3]!=cleanData[-1].split(",")[3]):
                    cleanData.append(nextRow)
            else:
                cleanData.append(self.cleanFirstRow(row))
        cleanData = "".join(cleanData)
        return cleanData

    def convertPalette(self, inputName, inputData):
        with open(os.path.join(self.INPUTPATH, inputName), "r") as inputFile:
            paletteText = "DEFINE_GRADIENT_PALETTE({})".format(inputName[:-4]) + "{\n"
            fileData = self.extractDataFromFile(inputFile.read())
            fileData = self.dropDuplicates(fileData)
            paletteText = paletteText + fileData + "};\n\n"
            inputData.extend(paletteText)
        return inputData

    def mainConverter(self):
        palettesData = []
        convertedPalettes = []
        palettesToConvert = [inputPalette for inputPalette in os.listdir(self.INPUTPATH) if(inputPalette.endswith(".c3g"))]
        for paletteToConvert in palettesToConvert:
            paletteToConvert = paletteToConvert.replace("-","_")
            # try:
            palettesData = self.convertPalette(paletteToConvert, palettesData)
            convertedPalettes.append(paletteToConvert)
            # except:
            #      pass
        self.fileWriter.writePalettesFile(convertedPalettes, palettesData)
