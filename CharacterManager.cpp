#include "CharacterManager.h"
#include "Floor.h"
#include "Baggage.h"
#include "Goal.h"
#include "Wall.h"
#include "Player.h"
#include "mapData.h"

CharacterManager::CharacterManager() {
	std::cout << "Create CharacterManager\n";
    character[FLOOR] = new Floor();
    character[BAGGAGE] = new Baggage(this);
    character[GOAL] = new Goal();
    character[WALL] = new Wall();
    character[PLAYER] = new Player(this);
    m_stageNum = 0;
}

CharacterManager::~CharacterManager() {
	std::cout << "Delete CharacterManager\n";
}

CharacterManager* CharacterManager::getInstance() {
    static CharacterManager instance;
    return &instance;
}

void CharacterManager::setCharacter(int stageNum) {
    int cnt = 0;
    int posX, posY;
    m_stageNum = stageNum;

    for (int y = 0;y < (SCREEN_HEIGHT / WALL_HEIGHT);y++) {
        for (int x = 0;x < (SCREEN_WIDTH / WALL_WIDTH);x++) {
            posX = x * WALL_WIDTH;
            posY = y * WALL_HEIGHT;
            if ((map[stageNum][cnt] != GOAL) &&
                (map[stageNum][cnt] != WALL) &&
                (map[stageNum][cnt] != BLANK)) {
                    character[FLOOR]->addCharacter(posX, posY);
            }
            else if (map[stageNum][cnt] == GOAL) {
                character[GOAL]->addCharacter(posX, posY);
            }
            else if (map[stageNum][cnt] == WALL) {
                character[WALL]->addCharacter(posX, posY);
            }
            if (map[stageNum][cnt] == BAGGAGE) {
                character[BAGGAGE]->addCharacter(posX, posY);
            }
            if (map[stageNum][cnt] == PLAYER) {
                character[PLAYER]->addCharacter(posX, posY);
            }

            cnt++;
        }
    }
}

void CharacterManager::setMap(Map* map) {
    m_map = map;
}

void CharacterManager::deleteCharacterManager() {
    for (int i = 0;i < CHARACTER_MAX;i++) {
        character[i]->clearCharacter();
    }
}

void CharacterManager::drawCharactert() {
    for (int i = 0;i < CHARACTER_MAX;i++) {
        character[i]->drawCharacter();
    }
}

int CharacterManager::getMoveResultPoint(int direct, int step) {
    position playerPos;
    int movePoint = 0;
    // �v���C���̈ʒu���
    auto playerItr = character[PLAYER]->lposition.begin();
    playerPos.offsetX = playerItr->offsetX;
    playerPos.offsetY = playerItr->offsetY;

    // �v���C���[�ƕǓ����蔻��
    movePoint = getMovePoint_wall(&playerPos, direct, step, false);
    // �v���C���[�Ɖו������蔻��i�ו��͈ړ��ł���j
    if (movePoint != 0) {
        movePoint = getMovePoint_bag(&playerPos, direct, movePoint);
    }

    return movePoint;
}

bool CharacterManager::isObstraction(int direct, position* myPosition, position* othPosition) {

    bool rbool = false;

    switch (direct) {
    case EventAdapter::EVENT_UP:
        if ((myPosition->offsetY >= (othPosition->offsetY + CHARACTER_HEIGHT)) &&
            (((myPosition->offsetX >= othPosition->offsetX) &&
                (myPosition->offsetX < (othPosition->offsetX + CHARACTER_WIDTH))) ||
                ((othPosition->offsetX >= myPosition->offsetX) &&
                    (othPosition->offsetX < (myPosition->offsetX + CHARACTER_WIDTH))))) {
            rbool = true;
        }
        break;
    case EventAdapter::EVENT_RIGHT:
        if ((othPosition->offsetX >= (myPosition->offsetX + CHARACTER_WIDTH)) &&
            (((myPosition->offsetY >= othPosition->offsetY) &&
                (myPosition->offsetY < (othPosition->offsetY + CHARACTER_HEIGHT))) ||
                ((othPosition->offsetY >= myPosition->offsetY) &&
                    (othPosition->offsetY < (myPosition->offsetY + CHARACTER_HEIGHT))))) {
            rbool = true;
        }
        break;
    case EventAdapter::EVENT_DOWN:
        if ((othPosition->offsetY >= (myPosition->offsetY + CHARACTER_HEIGHT)) &&
            (((myPosition->offsetX >= othPosition->offsetX) &&
                (myPosition->offsetX < (othPosition->offsetX + CHARACTER_WIDTH))) ||
                ((othPosition->offsetX >= myPosition->offsetX) &&
                    (othPosition->offsetX < (myPosition->offsetX + CHARACTER_WIDTH))))) {
            rbool = true;
        }
        break;
    case EventAdapter::EVENT_LEFT:
        if ((myPosition->offsetX >= (othPosition->offsetX + CHARACTER_WIDTH)) &&
            (((myPosition->offsetY >= othPosition->offsetY) &&
                (myPosition->offsetY < (othPosition->offsetY + CHARACTER_HEIGHT))) ||
                ((othPosition->offsetY >= myPosition->offsetY) &&
                    (othPosition->offsetY < (myPosition->offsetY + CHARACTER_HEIGHT))))) {
            rbool = true;
        }
        break;
    default:
        break;
    }

    return rbool;
}

// ��Q��(othPosition)�܂ōő�maxMovePoint�i�ށBmaxMovePoint�i�߂Ȃ����͐i�߂邾���i��(rPoint)
int CharacterManager::getMovePoint(int direct, position* myPosition, position* othPosition, int maxMovePoint) {

    int rPoint = maxMovePoint;

    switch (direct) {
    case EventAdapter::EVENT_UP:
        if ((myPosition->offsetY - (othPosition->offsetY + CHARACTER_HEIGHT)) < maxMovePoint) {
            rPoint = (myPosition->offsetY - (othPosition->offsetY + CHARACTER_HEIGHT));
        }
        break;
    case EventAdapter::EVENT_RIGHT:
        if ((othPosition->offsetX - (myPosition->offsetX + CHARACTER_WIDTH)) < maxMovePoint) {
            rPoint = (othPosition->offsetX - (myPosition->offsetX + CHARACTER_WIDTH));
        }
        break;
    case EventAdapter::EVENT_DOWN:
        if ((othPosition->offsetY - (myPosition->offsetY + CHARACTER_HEIGHT)) < maxMovePoint) {
            rPoint = (othPosition->offsetY - (myPosition->offsetY + CHARACTER_HEIGHT));
        }
        break;
    case EventAdapter::EVENT_LEFT:
        if ((myPosition->offsetX - (othPosition->offsetX + CHARACTER_WIDTH)) < maxMovePoint) {
            rPoint = (myPosition->offsetX - (othPosition->offsetX + CHARACTER_WIDTH));
        }
        break;
    default:
        break;
    }


    return rPoint;
}

int CharacterManager::getMovePoint_wall(position* myPosition, int direct, int step, bool bagFlag) {
    position wallPos;
    position bagPos;
    int tStep = step;
    int rStep = step;
    // �ǂ̈ʒu���
    auto wallItr = character[WALL]->lposition.begin();
    int wallSize = character[WALL]->lposition.size();
    // �ו��̈ʒu���
    auto bagItr = character[BAGGAGE]->lposition.begin();
    int bagSize = character[BAGGAGE]->lposition.size();

    for (int i = 0;i < wallSize;i++) {
        wallPos.offsetX = wallItr->offsetX;
        wallPos.offsetY = wallItr->offsetY;
        // �Ԃ��蔻��Ώۂ�����
        if (isObstraction(direct, myPosition, &wallPos) == true) {
            tStep = getMovePoint(direct, myPosition , &wallPos, rStep);
            if (tStep < rStep) {
                rStep = tStep;
            }
        }
        if (rStep == 0) {
            // �����Ȃ����Ƃ����肵���̂ŁA�ȍ~�̔���͍s��Ȃ�
            break;
        }
        wallItr++;
    }

    // bagFlag(= true)���͑��̉ו��͕ǈ����ɂ���i�ו����A�Ȃ������͓����Ȃ�����j
    if (bagFlag == true) {
        for (int i = 0;i < bagSize;i++) {
            bagPos.offsetX = bagItr->offsetX;
            bagPos.offsetY = bagItr->offsetY;
            if ((myPosition->offsetX != bagPos.offsetX) || (myPosition->offsetY != bagPos.offsetY)) {
                if (isObstraction(direct, myPosition, &bagPos)) {
                    tStep = getMovePoint(direct, myPosition, &bagPos, rStep);
                    if (tStep < rStep) {
                        rStep = tStep;
                    }
                    if (rStep == 0) {
                        // �����Ȃ����Ƃ����肵���̂ŁA�ȍ~�̔���͍s��Ȃ�
                        break;
                    }
                }
            }
            bagItr++;
        }
    }

    return rStep;
}

// �ו����l�������ړ��ʂ�Ԃ�
// �ו��̈ړ���̈ʒu�X�V���s��
int CharacterManager::getMovePoint_bag(position* mPosition, int direct, int step) {

    position bagPos;
    struct tmpbag {
        int id;
        int touchDistance;
    };
#define TMP_MAX 2
    tmpbag TmpbagPos[TMP_MAX];
    int cnt = 0;
    for (int i = 0;i < TMP_MAX;i++) {
        memset(&TmpbagPos[i], 0, sizeof(tmpbag));
    }

    // �ו��̈ʒu���
    auto bagItr = character[BAGGAGE]->lposition.begin();
    int bagSize = character[BAGGAGE]->lposition.size();
    int toBagMovePoint = step;
    int bagMovePoint = 0;
    int minumMovepoint = 10000;

    // �ו��܂ł̋������Z�o
    for (int i = 0;i < bagSize;i++) {
        bagPos.id = bagItr->id;
        bagPos.offsetX = bagItr->offsetX;
        bagPos.offsetY = bagItr->offsetY;

        if (isObstraction(direct, mPosition, &bagPos)) {
            // toBagMovePoint = �ו��܂ł̋��� 
            toBagMovePoint = getMovePoint(direct, mPosition, &bagPos, step);
            if (toBagMovePoint < step) {
                // bagMovePoint = �ו��̈ړ���
                bagMovePoint = getMovePoint_wall(&bagPos, direct, (step - toBagMovePoint), true);
                if (bagMovePoint > 0) {
                    // ��xbag�܂ł̋�����ۑ����Ă����i���Ƃōŏ��l���������bag�ړ��ʂɕύX�j
                    if (cnt == TMP_MAX) {
                        std::cout << "getMovePoint_bag error cnt:" << cnt << "\n";
                    }
                    else {
                        TmpbagPos[cnt].id = bagPos.id;
                        TmpbagPos[cnt].touchDistance = toBagMovePoint;
                        cnt++;
                    }
                }
                if (minumMovepoint > (toBagMovePoint + bagMovePoint)) {
                    // �v���C���[�ړ�����
                    minumMovepoint = (toBagMovePoint + bagMovePoint);
                }
            }
        }
        bagItr++;
    }

    for (int i = 0;i < cnt;i++) {
        if (minumMovepoint > TmpbagPos[cnt].touchDistance) {
            Baggage* bagPtr = (Baggage*)character[BAGGAGE];
            bagPtr->move(TmpbagPos[i].id, direct, (minumMovepoint - TmpbagPos[i].touchDistance));
        }
    }


    // �ړ��ʂ��X�V����Ă��Ȃ�(= �ו��Ƃ̐ڐG�Ȃ�)
    if (minumMovepoint == 10000) {
        minumMovepoint = step;
    }

    return minumMovepoint;
}

bool CharacterManager::isBagGaol() {

    int j;

    // �S�[���̈ʒu���
    auto goalItr = character[GOAL]->lposition.begin();
    int goalSize = character[GOAL]->lposition.size();

    // �S�[���ɍ��W����v���Ă���ו������邩�`�F�b�N����
    for (int i = 0;i < goalSize;i++) {
        auto bagItr = character[BAGGAGE]->lposition.begin();
        int bagSize = character[BAGGAGE]->lposition.size();
        for (j = 0;j < bagSize;j++) {
            if ((goalItr->offsetX == bagItr->offsetX) &&
                (goalItr->offsetY == bagItr->offsetY)) {
                break;
            }
            bagItr++;
        }
        if (j == bagSize) {
            // �S�[���ɓ����Ă���ו����Ȃ�����
            return false;
        }
        goalItr++;
    }

    // ���ׂẲו���GOAL�ɓ����Ă���
    m_map->receiveGoalEvent();
    return true;
}

void CharacterManager::setMoveAccept(bool accept) {
    Player* playerPtr = (Player *)character[PLAYER];
    playerPtr->setMoveAccept(accept);
}

