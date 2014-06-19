/// @filename PluginEditor.cpp
/// @brief SandBox plugin editor (UI & control)
/// @author gm
/// @copyright gm 2013
///
/// This file is part of SandBox
///
/// SandBox is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// SandBox is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with SandBox.  If not, see <http://www.gnu.org/licenses/>.


// This file is NOT generated by Juce (at least not after the first time),
// That's why we apply our coding style here

#include "sandbox/implementation/plugin/vst/PluginEditor.h"

#include "sandbox/src/common.h"

SandBoxAudioProcessorEditor::SandBoxAudioProcessorEditor(
    SandBoxAudioProcessor* owner)
    : AudioProcessorEditor(owner),
      debug_infos_() {

  // DEBUG
  addAndMakeVisible(&debug_infos_);
  this->startTimer(kTimerInterval);
  //  /DEBUG

  getProcessor()->addChangeListener(this);
  // This is where our plugin's editor size is set.
  setSize(kMainWindowSizeX, kMainWindowSizeY);
}

SandBoxAudioProcessorEditor::~SandBoxAudioProcessorEditor() {
  getProcessor()->removeChangeListener(this);
}

void SandBoxAudioProcessorEditor::paint(juce::Graphics& g) {
  g.fillAll(Colours::white);

  // DEBUG
  debug_infos_.setBounds(0, 350, this->getWidth(), 100);
  //  /DEBUG
}

void SandBoxAudioProcessorEditor::changeListenerCallback(
    juce::ChangeBroadcaster *source) {
  SandBoxAudioProcessor* proc(getProcessor());
  // No other change broacaster than the processor for now!
  SANDBOX_ASSERT(source == proc);
  // Inform all UI subcomponents of any change
  sendChangeMessage();
}

void SandBoxAudioProcessorEditor::timerCallback() {
  const double time(getProcessor()->GetLastProcessTime());
  debug_infos_.setText(juce::String(time));
}

float SandBoxAudioProcessorEditor::GetParamValue(const int param_id) {
  return getProcessor()->getParameter(param_id);
}

void SandBoxAudioProcessorEditor::ParamValueChanged(const int param_id,
                                                     const float value) {
  getProcessor()->setParameterNotifyingHost(param_id, value);
}

void SandBoxAudioProcessorEditor::ParamGestureBegan(const int param_id) {
  getProcessor()->beginParameterChangeGesture(param_id);
}

void SandBoxAudioProcessorEditor::ParamGestureEnded(const int param_id) {
  getProcessor()->endParameterChangeGesture(param_id);
}

SandBoxAudioProcessor* SandBoxAudioProcessorEditor::getProcessor() const {
  return static_cast<SandBoxAudioProcessor*>(getAudioProcessor());
}
