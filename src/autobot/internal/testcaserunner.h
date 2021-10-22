﻿/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef MU_AUTOBOT_TESTCASERUNNER_H
#define MU_AUTOBOT_TESTCASERUNNER_H

#include <vector>
#include <memory>
#include <QJSValue>
#include <QEventLoop>

#include "async/channel.h"
#include "async/asyncable.h"
#include "ret.h"
#include "io/path.h"

#include "autobottypes.h"

namespace mu::autobot {
class TestCaseRunner : public async::Asyncable
{
public:
    TestCaseRunner() = default;

    void setStepsInterval(int msec);
    void runTestCase(const TestCase& testCase);
    void abortTestCase();

    async::Channel<QString /*name*/> stepStarted() const;
    async::Channel<QString /*name*/> stepFinished() const;
    async::Channel<bool /*aborted*/> allFinished() const;

private:

    struct TestCaseData
    {
        TestCase testCase;
        Steps steps;
        int stepsCount = 0;
        int currentStepIdx = -1;
        int finishedCount = 0;
        QEventLoop loop;
    };

    void nextStep();

    int m_intervalMsec = 1000;
    TestCaseData m_testCase;
    bool m_abort = false;

    async::Channel<QString /*name*/> m_stepStarted;
    async::Channel<QString /*name*/> m_stepFinished;
    async::Channel<bool /*aborted*/> m_allFinished;
};
}

#endif // MU_AUTOBOT_TESTCASERUNNER_H