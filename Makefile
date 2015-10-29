SOURCE_DIR = src

all:
	cd $(SOURCE_DIR) && $(MAKE)

clean:
	cd $(SOURCE_DIR) && $(MAKE) clean