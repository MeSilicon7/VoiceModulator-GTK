#include <stdio.h>
#include <stdlib.h>
#include <portaudio.h>
#include <soundtouch/SoundTouch.h>
#include <gtk/gtk.h>
#include <pthread.h>

using namespace soundtouch;

// Global sound processor
SoundTouch soundTouch;

// Audio callback function
static int audioCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData) {
    float *in = (float*)inputBuffer;
    float *out = (float*)outputBuffer;

    // Process pitch, tempo, and formant shift
    soundTouch.putSamples(in, framesPerBuffer);
    soundTouch.receiveSamples(out, framesPerBuffer);

    return paContinue;
}

// Initialize PortAudio stream
void initAudio() {
    PaStream *stream;
    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, 44100, 256, audioCallback, NULL);
    Pa_StartStream(stream);
}

// Audio thread function
void* audioThread(void *arg) {
    initAudio();
    return NULL;
}

// Callback for adjusting pitch
void on_pitch_adjust(GtkRange *range, gpointer data) {
    float pitch = gtk_range_get_value(range);
    soundTouch.setPitch(pitch);
}

// Callback for adjusting tempo
void on_tempo_adjust(GtkRange *range, gpointer data) {
    float tempo = gtk_range_get_value(range);
    soundTouch.setTempo(tempo);
}

// Callback for adjusting formant
void on_formant_adjust(GtkRange *range, gpointer data) {
    float formant = gtk_range_get_value(range);
    soundTouch.setRateChange(formant);
}

// Setup GTK window with sliders for control
void createWindow() {
    GtkWidget *window, *vbox, *pitch_slider, *tempo_slider, *formant_slider;
    GtkWidget *pitch_label, *tempo_label, *formant_label;

    gtk_init(NULL, NULL);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    pitch_label = gtk_label_new("Pitch Adjustment");
    tempo_label = gtk_label_new("Tempo Adjustment");
    formant_label = gtk_label_new("Formant Adjustment");

    pitch_slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.5, 2.0, 0.1);
    gtk_range_set_value(GTK_RANGE(pitch_slider), 1.0);

    tempo_slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.5, 2.0, 0.1);
    gtk_range_set_value(GTK_RANGE(tempo_slider), 1.0);

    formant_slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -12, 12, 1);
    gtk_range_set_value(GTK_RANGE(formant_slider), 0);

    g_signal_connect(pitch_slider, "value-changed", G_CALLBACK(on_pitch_adjust), NULL);
    g_signal_connect(tempo_slider, "value-changed", G_CALLBACK(on_tempo_adjust), NULL);
    g_signal_connect(formant_slider, "value-changed", G_CALLBACK(on_formant_adjust), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), pitch_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), pitch_slider, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), tempo_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), tempo_slider, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), formant_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), formant_slider, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    pthread_t audio_thread;

    // Initialize SoundTouch settings
    soundTouch.setSampleRate(44100);
    soundTouch.setChannels(1);

    // Create and start audio thread
    pthread_create(&audio_thread, NULL, audioThread, NULL);

    // Create GTK window
    createWindow();

    // Wait for audio thread to finish
    pthread_join(audio_thread, NULL);

    return 0;
}
