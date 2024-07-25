# VoiceModulator-GTK
Real-time voice modulation software with pitch, tempo, and timbre control using GTK

### Prerequisites

1. **MSYS2**:
   - Download and install MSYS2 from [msys2.org](https://www.msys2.org/).

2. **Libraries**:
   - `portaudio`
   - `soundtouch`
   - `gtk+-3.0`

### Installation

#### Step 1: Install MSYS2

Download and install MSYS2 from the [official website](https://www.msys2.org/). Follow the installation instructions provided there.

#### Step 2: Update MSYS2

Open the MSYS2 terminal and update the package database and core system packages:

```sh
pacman -Syu
```

Close and reopen the MSYS2 terminal.

#### Step 3: Install Dependencies

Install the required libraries and development tools:

```sh
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-gtk3
pacman -S mingw-w64-x86_64-portaudio
pacman -S mingw-w64-x86_64-soundtouch
```

#### Step 4: Clone the Repository

Clone this repository to your local machine:

```sh
git clone https://github.com/MeSilicon7/VoiceModulator-GTK.git
cd VoiceModulator-GTK
```

#### Step 5: Build the Application

Build the application using `g++`:

```sh
g++ `pkg-config --cflags gtk+-3.0` -o my_program3 main.cpp `pkg-config --libs gtk+-3.0 portaudio-2.0 soundtouch`
```

### Running the Application

Run the built application from the MSYS2 terminal:

```sh
./my_program3
```

### Usage

1. **Adjust Pitch**: Use the pitch slider to change the pitch of the audio input.
2. **Adjust Tempo**: Use the tempo slider to change the tempo.
3. **Adjust Formant**: Use the formant slider to shift the formants.
4. **Monitor**: Click the "Start Monitoring" button to start processing the audio input. Click again to stop.

### Contributing

Feel free to submit issues or pull requests. For major changes, please open an issue first to discuss what you would like to change.

### License

No License

### Acknowledgements

- [PortAudio](http://www.portaudio.com/)
- [SoundTouch](http://www.surina.net/soundtouch/)
- [GTK](https://www.gtk.org/)

