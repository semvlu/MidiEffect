#pragma once
#include "JuceHeader.h"
constexpr int interal = 4;
class MidiProcessor
{
public:
    void process(juce::MidiBuffer& midiMessages)
    {
        processedBuffer.clear();
        juce::MidiBuffer::Iterator it(midiMessages);
        juce::MidiMessage currentMessage;
        int samplePos;
        while (it.getNextEvent(currentMessage, samplePos))
        {
            if(currentMessage.isNoteOnOrOff())
            {
                auto transposedMessage = currentMessage;
                auto oldNoteNum = transposedMessage.getNoteNumber();
                transposedMessage.setNoteNumber(oldNoteNum + interal);
                processedBuffer.addEvent(transposedMessage, samplePos);
            }
            processedBuffer.addEvent(currentMessage, samplePos);
        }
        midiMessages.swapWith(processedBuffer);
    }
    juce::MidiBuffer processedBuffer;
};
