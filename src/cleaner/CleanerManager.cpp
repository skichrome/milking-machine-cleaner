#include "cleaner/CleanerManager.h"

CleanerManager::CleanerManager(CleanColdWaterManager *mColdWaterCleaner, CleanHotWaterManager *mHotWaterCleaner, const char **mFirstLineMsg, const char **mSecondLineMsg)
{
    coldWaterCleaner = mColdWaterCleaner;
    hotWaterCleaner = mHotWaterCleaner;
    firstLineMsg = mFirstLineMsg;
    secondLineMsg = mSecondLineMsg;
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
            runColdClean(true, false);
            break;
        case CleanState::CLEAN:
            runHotClean(false);
            break;
        case CleanState::CLEAN_COLD:
            runHotClean(true);
            break;
        case CleanState::RINCE:
            runColdClean(false, false);
            break;
        case CleanState::RINCE_AND_DRY:
            runColdClean(false, true);
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

void CleanerManager::runColdClean(bool isPreHeatRequired, bool dryRequired)
{
    if (!coldWaterCleaner->isStarted())
        coldWaterCleaner->start(isPreHeatRequired, dryRequired, firstLineMsg, secondLineMsg);

    if (coldWaterCleaner->isDone())
    {
        coldWaterCleaner->resetIfDone();
        currentRunningStep++;
    }
}

void CleanerManager::runHotClean(bool coldCleanMode)
{
    if (!hotWaterCleaner->isStarted())
        hotWaterCleaner->start(coldCleanMode, firstLineMsg, secondLineMsg);

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

void CleanerManager::pauseOrResumeFill()
{
    if (coldWaterCleaner->isFillingPaused())
        coldWaterCleaner->resumeFillingWater();
    else if (coldWaterCleaner->isStarted())
        coldWaterCleaner->pauseFillingWater();

    if (hotWaterCleaner->isFillingPaused())
        hotWaterCleaner->resumeFillingWater();
    else if (hotWaterCleaner->isStarted())
        hotWaterCleaner->pauseFillingWater();

    if (hotWaterCleaner->isStarted())
        hotWaterCleaner->endEvacuate();
}