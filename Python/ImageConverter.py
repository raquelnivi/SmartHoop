import re, os

class ImageConverter():

    fileWriter:object
    INPUTPATH:str
    OUTPUTPATH:str
    imageNames:list=[]
    TEMPLATE = "// Source file name: %SOURCE%\n\n\n#include <stdint.h>\n#ifdef __AVR__\n#define _PGM_ PROGMEM\n#else\n#define _PGM_\n#endif\n\n\nstatic const uint8_t %ITEMNAME%[] _PGM_ = {\n\n%CONTENT%\n};\n"

    def __init__(self, fileWriter, INPUTPATH, OUTPUTPATH):
        self.fileWriter = fileWriter
        self.INPUTPATH = INPUTPATH
        self.OUTPUTPATH = OUTPUTPATH

    def chunkBy(self, sequence, chunkSize):
        """ Yield successive chunks of length chunkSize from sequence. """
        for i in range(0, len(sequence), chunkSize):
            yield sequence[i:i+chunkSize]

    def createContent(self, asHex):
        content = ""
        offset = 0
        for chunk in self.chunkBy(asHex, 16):
            content += "    /* 0x%04x: */ " % offset
            content += ", ".join(chunk)
            content += ",\n"
            offset += 16
        return content

    def generateOutput(self, content, sourceName, destinationName):    
        output = self.TEMPLATE
        output = output.replace("%CONTENT%", content)
        output = output.replace("%SOURCE%", sourceName)
        itemname = re.sub(r'[^a-zA-Z0-9]', '_',  os.path.splitext(destinationName)[0])
        output = output.replace("%ITEMNAME%", itemname)
        with open(os.path.join(self.OUTPUTPATH, "images", destinationName), "wb") as destination:
            destination.write(bytes(output, 'UTF-8'))

    def convertImage(self, inputName, outputName):
        with open(os.path.join(self.INPUTPATH, inputName), "rb") as inputFile:
            inputData = inputFile.read()
        # if(len(inputData)>32768):
        #     raise Exception
        asHex = [("0x%02x" % b) for b in inputData]
        content = self.createContent(asHex)
        output = self.generateOutput(content, inputName, outputName)

    def mainConverter(self):
        convertedImages = []
        imagesToConvert = [inputImage for inputImage in os.listdir(self.INPUTPATH) if(inputImage.endswith(".bmp"))]
        for imageToConvert in imagesToConvert[:20]:
            imageToConvert = imageToConvert.replace("-","_")
            outputName = imageToConvert.replace(".bmp",".h")
            try:
                self.convertImage(imageToConvert, outputName)
                convertedImages.append(outputName)
            except:
                 pass
        self.fileWriter.writeImagesFile(convertedImages)