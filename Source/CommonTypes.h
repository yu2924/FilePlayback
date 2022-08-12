//
//  CommonTypes.h
//  FilePlayback_SharedCode
//
//  created by yu2924 on 2022-08-13
//  (c) 2022 yu2924
//

#pragma once

#include <JuceHeader.h>

struct TimeRange
{
    double begin, end;
    juce::var toVar() const
    {
        return juce::Array<juce::var>{ juce::var(begin), juce::var(end) };
    }
    static TimeRange fromVar(const juce::var& v)
    {
        if(!v.isArray() || (v.size() != 2)) return {};
        return { (double)v[0], (double)v[1] };
    }
};
