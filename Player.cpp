#include "Player.h"
#include "Controlar.h"

Player::Player() {
	std::cout << "Create Player\n";
	direct = EventAdapter::EVENT_DOWN;
	// 読み込みファイル
	file = new Mat;
	*file = imread(CHARACTER_FILE_PATH, -1);
	// キャラクターイメージ
	setImageFile();
}

Player::Player(CharacterManager* characterManager) {
	std::cout << "Create Player (CharacterManager*)\n";
	m_characterManager = characterManager;
	// 移動量
	step = 4;
	direct = EventAdapter::EVENT_DOWN;
	count = 0;
	// 読み込みファイル
	file = new Mat;
	*file = imread(CHARACTER_FILE_PATH, -1);
	// キャラクターイメージ
	setImageFile();
	// コントローラ設定
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
	// リスト要素全消去
	lposition.clear();
	direct = EventAdapter::EVENT_DOWN;
	count = 0;
	// 初期パターン設定
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

	// キャラクタパターン決定変数
	int offX = (count / PATTERN_SPEED);

	// 方向キャラ決定変数
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
	// 表示キャラクター更新
	setImageFile();
	// 位置更新
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

	// 移動量算出
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
        // ポインタの取得
        src_ptr = src->ptr<cv::Vec4b>(y);
        dst_ptr = dst->ptr<cv::Vec4b>(y);
        for (int x = 0; x < src->cols; x++) {
            // 値の取得
            src_bgra = src_ptr[x];
            dst_bgra = dst_ptr[x];
            // 透過率100%時はdstのデータは更新しない
            if (src_bgra[3] != 0) {
                // dst のalpha は更新しない
                dst_ptr[x] = cv::Vec4b(src_bgra[0], src_bgra[1], src_bgra[2], dst_bgra[3]);
            }
        }
    }
}

void Player::setMoveAccept(bool accept) {
	moveAcceptFlag = accept;
}



