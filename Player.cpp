#include "Player.h"
#include "Controlar.h"

Player::Player() {
	std::cout << "Create Player\n";
	direct = EventAdapter::EVENT_DOWN;
	// �ǂݍ��݃t�@�C��
	file = new Mat;
	*file = imread(CHARACTER_FILE_PATH, -1);
	// �L�����N�^�[�C���[�W
	setImageFile();
}

Player::Player(CharacterManager* characterManager) {
	std::cout << "Create Player (CharacterManager*)\n";
	m_characterManager = characterManager;
	// �ړ���
	step = 4;
	direct = EventAdapter::EVENT_DOWN;
	count = 0;
	// �ǂݍ��݃t�@�C��
	file = new Mat;
	*file = imread(CHARACTER_FILE_PATH, -1);
	// �L�����N�^�[�C���[�W
	setImageFile();
	// �R���g���[���ݒ�
	m_controlar = new Controlar(this);
	std::thread th_a(*m_controlar);
	th_a.detach();
	moveAcceptFlag = false;
}

void Player::drawCharacter() {
	auto itr = lposition.begin();
	int size = lposition.size();
	Mat* image_clip = NULL;

	for (int i = 0;i < size;i++) {
		image_clip = new Mat(*m_screen,
			Rect(itr->offsetX, itr->offsetY,
				CHARACTER_WIDTH, CHARACTER_HEIGHT));

		overlayChar(character, image_clip);
		delete(image_clip);
		itr++;
	}
}

void Player::clearCharacter() {
	// ���X�g�v�f�S����
	lposition.clear();
	direct = EventAdapter::EVENT_DOWN;
	count = 0;
	// �����p�^�[���ݒ�
	setImageFile();
}

void Player::drawCharacterPosition(int offX, int offY) {
	Mat* image_clip = NULL;

	image_clip = new Mat(*m_screen,
		Rect(offX, offY,
			CHARACTER_WIDTH, CHARACTER_HEIGHT));

	overlayChar(character, image_clip);
	delete(image_clip);
}

void Player::setImageFile() {

	// �L�����N�^�p�^�[������ϐ�
	int offX = (count / PATTERN_SPEED);

	// �����L��������ϐ�
	int offY = 0;

	if (direct == EventAdapter::EVENT_DOWN) {
		offY = 0;
	}
	else if (direct == EventAdapter::EVENT_LEFT) {
		offY = 1;
	}
	else if (direct == EventAdapter::EVENT_RIGHT) {
		offY = 2;
	}
	else if (direct == EventAdapter::EVENT_UP) {
		offY = 3;
	}
	Character::setImageFile(CHARACTER_FILE_PATH, CHARACTER_WIDTH, CHARACTER_HEIGHT, offX, offY);
}

int Player::ReceiveEvent(int event) {
	int movePoint = 0;
	if (moveAcceptFlag == false) {
		return 0;
	}

	direct = event;
	// �\���L�����N�^�[�X�V
	setImageFile();
	// �ʒu�X�V
	movePoint = move(event, step);

	if (count == ((PATTERN_MAX * PATTERN_SPEED) - 1)) {
		count= 0;
	}
	else {
		count++;
	}
	return movePoint;
}

int Player::move(int direct, int step) {
	auto itr = lposition.begin();
	int size = lposition.size();
	int fStep = 0;
	
	if (size == 0) {
		return 0;
	}

	// �ړ��ʎZ�oXXX
	fStep = m_characterManager->getMoveResultPoint(direct, step);

	switch (direct) {
	case EventAdapter::EVENT_UP:
		itr->offsetY -= fStep;
		break;
	case EventAdapter::EVENT_DOWN:
		itr->offsetY += fStep;
		break;
	case EventAdapter::EVENT_RIGHT:
		itr->offsetX += fStep;
		break;
	case EventAdapter::EVENT_LEFT:
		itr->offsetX -= fStep;
		break;
	}

	return fStep;
}

void Player::setCharacterManagerPtr(CharacterManager* ptr) {
	m_characterManager = ptr;
}

void Player::overlayChar(Mat* src, Mat* dst) {

    cv::Vec4b* src_ptr = NULL;
    cv::Vec4b src_bgra = NULL;
    cv::Vec4b* dst_ptr = NULL;
    cv::Vec4b dst_bgra = NULL;

    for (int y = 0; y < src->rows; y++) {
        // �|�C���^�̎擾
        src_ptr = src->ptr<cv::Vec4b>(y);
        dst_ptr = dst->ptr<cv::Vec4b>(y);
        for (int x = 0; x < src->cols; x++) {
            // �l�̎擾
            src_bgra = src_ptr[x];
            dst_bgra = dst_ptr[x];
            // ���ߗ�100%����dst�̃f�[�^�͍X�V���Ȃ�
            if (src_bgra[3] != 0) {
                // dst ��alpha �͍X�V���Ȃ�
                dst_ptr[x] = cv::Vec4b(src_bgra[0], src_bgra[1], src_bgra[2], dst_bgra[3]);
            }
        }
    }
}

void Player::setMoveAccept(bool accept) {
	moveAcceptFlag = accept;
}



