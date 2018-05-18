class DataProcessor:

	def __init__(self, duration = 1, chunklength=0.37):
		self.duration = duration
		self.audio = []
		self.currentLength = 0
		self.chunkLength = chunklength
	
	def setChunk(self, chunkLength):
		self.chunkLength = chunkLength

	def getAudio(self):
		audio = self.audio
		self.audio = []
		return audio

	def process(self, audioChunk):
		if self.currentLength < self.duration:
			self.audio.append(audioChunk)
			self.currentLength += self.chunkLength
			return (0, [])
		else:
			audio = self.getAudio()
			self.audio.append(audioChunk)
			self.currentLength = self.chunkLength
			return (1, audio)
		