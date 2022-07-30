#include "cleaner/CleanerManager.h"

CleanerManager::CleanerManager(CleanColdWaterManager *mColdWaterCleaner, CleanHotWaterManager *mHotWaterCleaner, const char **msgToDisplay)
{
    coldWaterCleaner = mColdWaterCleaner;
    hotWaterCleaner = mHotWaterCleaner;
    screenMsg = msgToDisplay;
}

void CleanerManager::setup()
{
    isCleanStarted = false;
    state = State::WAITING_START;
}

void CleanerManager::loop()
{
    if (isCleanStarted && currentRunningStep >= numberOfSteps)
    {
        currentCleanSequence = NULL;
        numberOfSteps = 0;
        isCleanStarted = false;

        coldWaterCleaner->resetIfDone();
        hotWaterCleaner->resetIfDone();
    }

    if (isCleanStarted)
    {
        switch (currentCleanSequence[currentRunningStep])
        {
        case CleanState::PREWASH:
            runColdClean(false);
            break;
        case CleanState::CLEAN:
            runHotClean(false);
            break;
        case CleanState::CLEAN_COLD:
            runHotClean(true);
            break;
        case CleanState::RINCE:
            runColdClean(false);
            break;
        case CleanState::RINCE_AND_DRY:
            runColdClean(true);
            break;

        default:
            break;
        }
    }
}

// --- Public command methods --- //

void CleanerManager::startNormalClean()
{
    if (!isCleanStarted)
    {
        isCleanStarted = true;
        currentRunningStep = 0;
        numberOfSteps = NORMAL_CLEAN_SEQ_SIZE;
        currentCleanSequence = normalCleanSequence;
    }
}

void CleanerManager::startCleanFromHotWater()
{
    if (!isCleanStarted)
    {
        isCleanStarted = true;
        currentRunningStep = 0;
        numberOfSteps = HOT_WATER_CLEAN_SEQ_SIZE;
        currentCleanSequence = hotWaterCleanSequence;
    }
}

void CleanerManager::startCleanFromFirstRince()
{
    if (!isCleanStarted)
    {
        isCleanStarted = true;
        currentRunningStep = 0;
        numberOfSteps = FIRST_RINCE_CLEAN_SEQ_SIZE;
        currentCleanSequence = firstRinceCleanSequence;
    }
}

void CleanerManager::startCleanFromSecondRince()
{
    if (!isCleanStarted)
    {
        isCleanStarted = true;
        currentRunningStep = 0;
        numberOfSteps = SECOND_RINCE_CLEAN_SEQ_SIZE;
        currentCleanSequence = secondRinceCleanSequence;
    }
}

void CleanerManager::startPeraceticClean()
{
    if (!isCleanStarted)
    {
        isCleanStarted = true;
        currentRunningStep = 0;
        numberOfSteps = PERACETIC_CLEAN_SEQ_SIZE;
        currentCleanSequence = peraceticCleanSequence;
    }
}

void CleanerManager::startImpactClean()
{
    if (!isCleanStarted)
    {
        isCleanStarted = true;
        currentRunningStep = 0;
        numberOfSteps = IMPACT_CLEAN_SEQ_SIZE;
        currentCleanSequence = impactCleanSequence;
    }
}

void CleanerManager::startOnlyHotWaterClean()
{
    if (!isCleanStarted)
    {
        isCleanStarted = true;
        currentRunningStep = 0;
        numberOfSteps = ONLY_HOT_WATER_CLEAN_SEQ_SIZE;
        currentCleanSequence = onlyHotWaterCleanSequence;
    }
}

void CleanerManager::startOnlyFirstRince()
{
    if (!isCleanStarted)
    {
        isCleanStarted = true;
        currentRunningStep = 0;
        numberOfSteps = ONLY_FIRST_RINCE_CLEAN_SEQ_SIZE;
        currentCleanSequence = onlyFirstRinceCleanSequence;
    }
}

// --- Common methods for clean --- //

void CleanerManager::runColdClean(bool dryRequired)
{
    if (!coldWaterCleaner->isStarted())
        coldWaterCleaner->start(dryRequired, screenMsg);

    if (coldWaterCleaner->isDone())
    {
        coldWaterCleaner->resetIfDone();
        currentRunningStep++;
    }
}

void CleanerManager::runHotClean(bool coldCleanMode)
{
    if (!hotWaterCleaner->isStarted())
        hotWaterCleaner->start(coldCleanMode, screenMsg);

    if (hotWaterCleaner->isDone())
    {
        hotWaterCleaner->resetIfDone();
        currentRunningStep++;
    }
}

bool CleanerManager::isBusy()
{
    return isCleanStarted;
}