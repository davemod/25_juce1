# 31. Oktober 2025

## Beispiel der Instanziierungsreihenfolge in C++ mit juce::HelloWorldAudioProcessorEditor


```c++

class HelloWorldAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    HelloWorldAudioProcessorEditor(HelloWorldAudioProcessor& p)
        : juce::AudioProcessorEditor(&p),  // 1. Base class zuerst in Initialisierungsliste
          audioProcessor(p),               // 2. Dann Member in Deklarationsreihenfolge
          gainSlider(),                    // 3. Default constructor für gainSlider
          gainLabel("Gain", "Gain")        // 4. Parametrisierter constructor für gainLabel
    {
        // 7. Constructor body wird als letztes ausgeführt
        std::cout << "HelloWorldAudioProcessorEditor constructor body\n";
        
        addAndMakeVisible(gainSlider);
        addAndMakeVisible(gainLabel);
        
        setSize(400, 300);
    }
    
    ~HelloWorldAudioProcessorEditor()
    {
        // 8. Destructor: umgekehrte Reihenfolge der Konstruktion
        std::cout << "HelloWorldAudioProcessorEditor destructor\n";
        // gainLabel wird zuerst zerstört, dann gainSlider, dann audioProcessor, dann base class
    }

private:
    HelloWorldAudioProcessor& audioProcessor; // Deklariert zuerst
    juce::Slider gainSlider;                  // Deklariert zweites  
    juce::Label gainLabel;                    // Deklariert drittes
};

// Instanziierungsreihenfolge beim Erstellen:
// 1. AudioProcessorEditor base class constructor
// 2. HelloWorldAudioProcessorEditor member initialization (audioProcessor, gainSlider, gainLabel)
// 3. HelloWorldAudioProcessorEditor constructor body




// Als Erinnerung: Hier wird der Editor erstellt ...
class HelloWorldAudioProcessor 
{
    // ...
    AudioProcessorEditor * createEditor ()
    {
        return new HelloWorldAudioProcessorEditor (*this);
    }
    // ...
}

```

