#include "PongGame.h"

PongGame::PongGame(int w, int h, int ballsz, int paddle_h, double ball_speed) :width(w), height(h), ballSize(ballsz), paddleHeight(paddle_h) {
	leftPaddle = height / 2;
	rightPaddle = height / 2;
	ballX = width / 2;
	ballY = height / 2;
	ballVX = rand() * 1.0 / RAND_MAX * 0.1 * ball_speed + 0.9 * ball_speed;
	ballVY = rand() * 1.0 / RAND_MAX * 0.1 * ball_speed + 0.9 * ball_speed;
	if (rand() % 2 == 0) {
		ballVX = -ballVX;
	}
	if (rand() % 2 == 0) {
		ballVY = -ballVY;
	}
}


void PongGame::changeLeftDirection(int direction) {
	leftPaddleDirection = direction;
}

void PongGame::changeRightDirection(int direction) {
	rightPaddleDirection = direction;
}

void PongGame::update() {
	if (!started) return;
	if (gameOver) return;
	leftPaddle += leftPaddleDirection * paddleSpeed;
	rightPaddle += rightPaddleDirection * paddleSpeed;

	if (leftPaddle - paddleHeight / 2 < 0) {
		leftPaddle = paddleHeight / 2;
	}
	if (leftPaddle + paddleHeight / 2 >= height) {
		leftPaddle = height - paddleHeight / 2.0;
	}

	if (rightPaddle - paddleHeight / 2 < 0) {
		rightPaddle = paddleHeight / 2;
	}
	if (rightPaddle + paddleHeight / 2 >= height) {
		rightPaddle = height - paddleHeight / 2.0;
	}

	ballX += ballVX;
	ballY += ballVY;

	bool ballInLeftPaddle = (ballY >= leftPaddle - paddleHeight / 2) && (ballY <= leftPaddle + paddleHeight / 2);
	bool ballInRightPaddle = (ballY >= rightPaddle - paddleHeight / 2) && (ballY <= rightPaddle + paddleHeight / 2);

	if (ballX - ballSize / 2 < 0 && ballVX < 0 && !ballInLeftPaddle) {
		gameOver = true;
		return;
	}
	if (ballX + ballSize / 2 > width && ballVX > 0 && !ballInRightPaddle) {
		gameOver = true;
		return;
	}

	if (ballInLeftPaddle && ballX - ballSize / 2 < paddleThinkness && ballVX < 0) {
		ballVX = -ballVX;
	}
	if (ballInRightPaddle && ballX + ballSize / 2 > width - paddleThinkness && ballVX > 0) {
		ballVX = -ballVX;
	}

	if (ballY - ballSize / 2 < 0 && ballVY < 0) {
		ballVY = -ballVY;
	}
	if (ballY + ballSize / 2 > height && ballVY > 0) {
		ballVY = -ballVY;
	}

}

void PongGame::render(SDL_Renderer* renderer) {
	SDL_Rect rect1 = { 0, (int)leftPaddle - paddleHeight / 2, paddleThinkness,  paddleHeight };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect1);


	SDL_Rect rect2 = { width - paddleThinkness ,(int)rightPaddle - paddleHeight / 2, paddleThinkness,  paddleHeight };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect2);

	SDL_Rect rect3 = { (int)ballX - ballSize / 2, (int)ballY - ballSize / 2, ballSize, ballSize };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect3);
}

void PongGame::startGame() {
	started = true;
}
