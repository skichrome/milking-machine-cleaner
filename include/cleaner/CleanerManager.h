#ifndef CLEANER_MANAGER_H
#define CLEANER_MANAGER_H

#include "CleanColdWaterManager.h"
#include "CleanHotWaterManager.h"

#define NORMAL_CLEAN_SEQ_SIZE 4
#define HOT_WATER_CLEAN_SEQ_SIZE 3
#define FIRST_RINCE_CLEAN_SEQ_SIZE 2
#define SECOND_RINCE_CLEAN_SEQ_SIZE 1
#define MILK_CONTROL_CLEAN_SEQ_SIZE 5
#define PERACETIC_CLEAN_SEQ_SIZE 2
#define IMPACT_CLEAN_SEQ_SIZE 5
#define ONLY_HOT_WATER_CLEAN_SEQ_SIZE 1
#define ONLY_FIRST_RINCE_CLEAN_SEQ_SIZE 1

class CleanerManager
{
private:
    const char **firstLineMsg;
    const char **secondLineMsg;

    bool isCleanStarted;
    unsigned int numberOfSteps;
    unsigned int currentRunningStep;

    enum State
    {
        WAITING_START,
        NORMAL_CLEAN,
        HOT_WATER_CLEAN,
        FIRST_RINCE_CLEAN,
        SECOND_RINCE_CLEAN,
        PERACETIC_CLEAN,
        IMPACT_CLEAN,
        ONLY_HOT_WATER_CLEAN,
        ONLY_FIRST_RINCE_CLEAN
    } state;

    enum CleanState
    {
        PREWASH,
        CLEAN,
        CLEAN_COLD,
        RINCE,
        RINCE_AND_DRY
    };

    CleanState *currentCleanSequence = NULL;

    CleanState normalCleanSequence[NORMAL_CLEAN_SEQ_SIZE] = {CleanState::PREWASH, CleanState::CLEAN, CleanState::RINCE, CleanState::RINCE_AND_DRY};
    CleanState hotWaterCleanSequence[HOT_WATER_CLEAN_SEQ_SIZE] = {CleanState::CLEAN, CleanState::RINCE, CleanState::RINCE_AND_DRY};
    CleanState firstRinceCleanSequence[FIRST_RINCE_CLEAN_SEQ_SIZE] = {CleanState::RINCE, CleanState::RINCE_AND_DRY};
    CleanState secondRinceCleanSequence[SECOND_RINCE_CLEAN_SEQ_SIZE] = {CleanState::RINCE_AND_DRY};
    CleanState milkControlCleanSequence[MILK_CONTROL_CLEAN_SEQ_SIZE] = {CleanState::PREWASH, CleanState::CLEAN, CleanState::RINCE, CleanState::CLEAN_COLD, CleanState::RINCE_AND_DRY};
    CleanState peraceticCleanSequence[PERACETIC_CLEAN_SEQ_SIZE] = {CleanState::CLEAN_COLD, CleanState::RINCE_AND_DRY};
    CleanState impactCleanSequence[IMPACT_CLEAN_SEQ_SIZE] = {CleanState::PREWASH, CleanState::CLEAN, CleanState::CLEAN, CleanState::RINCE, CleanState::RINCE_AND_DRY};
    CleanState onlyHotWaterCleanSequence[ONLY_HOT_WATER_CLEAN_SEQ_SIZE] = {CleanState::CLEAN};
    CleanState onlyFirstRinceCleanSequence[ONLY_FIRST_RINCE_CLEAN_SEQ_SIZE] = {CleanState::RINCE};

    CleanColdWaterManager *coldWaterCleaner;
    CleanHotWaterManager *hotWaterCleaner;

    void runNormalClean();
    void runCleanFromHotWater();
    void runCleanFromFirstRince();
    void runCleanFromSecondRince();
    void runPeraceticClean();
    void runImpactClean();
    void runOnlyHotWaterClean();
    void runOnlyFirstRince();

    void runColdClean(bool isPreHeatRequired, bool dryRequired);
    void runHotClean(bool coldCleanMode);

public:
    CleanerManager(CleanColdWaterManager *mColdWaterCleaner, CleanHotWaterManager *mHotWaterCleaner, const char **mFirstLineMsg, const char **mSecondLineMsg);

    void setup();
    void loop();

    void startNormalClean();
    void startCleanFromHotWater();
    void startCleanFromFirstRince();
    void startCleanFromSecondRince();
    void startPeraceticClean();
    void startImpactClean();
    void startOnlyHotWaterClean();
    void startOnlyFirstRince();

    bool isBusy();
    void pauseOrResumeFill();
};

#endif