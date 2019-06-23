#include "pch.h"
#include "Game.h"

//Timer definion

//0, Left Hold Delay
//1, Left Auto Repeat
//2, Right Hold Delay
//3, Right Auto Repeat
//4, Gravity Delay
//5, Soft Drop
//6, Line Clear Animation
//7, Line Clear Flash Delay
//8, Game Over Delay Start
//9, Game Over Animation Delay
//10, Game Over Delay End

void Game::resetKeyboard()
{
	downHold = false;
	leftHold = false;
	rightHold = false;
}

void Game::dropTetromino()
{
	for (auto piece : manager.getPiece()->getPieces())
	{
		if (board.checkPiece(piece.getPos().x, piece.getPos().y))
		{
			gameOver = true;
			timer.startTime(8, sf::milliseconds(1000));
			resetKeyboard();
		}
		board.addPiece(piece);
	}

	manager.removePiece();
}

void Game::spawnTeromino()
{
	timer.resetTime(4);
	if (!gameOver)
	{
		manager.addPiece(rng.getNum());
	}
}

void Game::startLineClearAnim()
{
	timer.startTime(6, sf::milliseconds(1000));
	timer.startTime(7, sf::milliseconds(200));
	board.flashLine();
	wait = true;
}

void Game::addScoreLine()
{
	int lineClear = board.GetLineClearCount();
	score->addClearLineScore(lineClear);
	score->addLineCleared(lineClear);
	score->updateLevel();
}

Game::Game(Render* p_renderer, Score* p_score)
{
	renderer = p_renderer;
	score = p_score;
	nextState = GAME_OVER;
}

void Game::activate()
{
	wait = false;
	gameOver = false;
	gameOverFillAnimation = false;
	gameOverFillLevel = board.getCol() - 1;
	resetKeyboard();
	board.reset();
	manager.addPiece(rng.getNum());
	timer.startTime(4, sf::milliseconds((lvlDropSpeed[score->getLevel()] * 1000) / 60));
	activated = true;
}

void Game::update()
{
	if (activated)
	{
		sf::Event event;

		while (renderer->getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				renderer->getWindow()->close();
			}

			if (!gameOver)
			{
				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
				{
					timer.startTime(0, sf::milliseconds(400));
					timer.startTime(1, sf::milliseconds(100));
					manager.getPiece()->moveLeft(board);
					leftHold = true;
				}
				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
				{
					timer.startTime(2, sf::milliseconds(400));
					timer.startTime(3, sf::milliseconds(100));
					manager.getPiece()->moveRight(board);
					rightHold = true;
				}
				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
				{
					timer.startTime(5, sf::milliseconds(50));
					manager.getPiece()->moveDown(board);
					downHold = true;
				}

				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
				{
					manager.getPiece()->rotate(board);
				}

				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Left))
				{
					timer.deleteTime(0);
					timer.deleteTime(1);
					leftHold = false;
				}
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Right))
				{
					timer.deleteTime(2);
					timer.deleteTime(3);
					rightHold = false;
				}
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Down))
				{
					timer.deleteTime(5);
					downHold = false;
				}
			}
		}

		if (manager.getPiece()->isDropped() and !wait)
		{
			dropTetromino();

			if (board.GetLineClearCount() > 0)
			{
				startLineClearAnim();
			}
			else
			{
				spawnTeromino();
			}
		}

		if (wait)
		{
			if (timer.isPassed(7))
			{
				board.flashLine();
				timer.resetTime(7);
			}

			if (timer.isPassed(6))
			{
				manager.addPiece(rng.getNum());
				addScoreLine();
				board.CheckRemoveLine();
				timer.resetTime(4);
				timer.deleteTime(6);
				timer.deleteTime(7);
				wait = false;
			}
		}

		if ((timer.isPassed(0)) and (leftHold))
		{
			if (timer.isPassed(1))
			{
				manager.getPiece()->moveLeft(board);
				timer.resetTime(1);
			}
		}

		if ((timer.isPassed(2)) and (rightHold))
		{
			if (timer.isPassed(3))
			{
				manager.getPiece()->moveRight(board);
				timer.resetTime(3);
			}
		}

		if (timer.isPassed(4) and (!downHold))
		{
			manager.getPiece()->moveDown(board);
			timer.resetTime(4);
		}

		if ((timer.isPassed(5)) and (downHold))
		{
			if (!wait)
			{
				score->addScore(1);
			}
			manager.getPiece()->moveDown(board);
			timer.resetTime(5);
		}

		if (gameOver)
		{
			if (timer.isPassed(8))
			{
				timer.deleteTime(8);
				timer.startTime(9, sf::milliseconds(100));
				gameOverFillAnimation = true;
			}

			if (gameOverFillAnimation)
			{
				if (timer.isPassed(9))
				{
					for (int x = 0; x < board.getRow(); ++x)
					{
						board.addPiece(Piece(14, x, gameOverFillLevel));
					}
					gameOverFillLevel--;
					timer.resetTime(9);
					if (gameOverFillLevel < 3)
					{
						timer.deleteTime(9);
						gameOverFillAnimation = false;
						timer.startTime(10, sf::milliseconds(1000));
					}
				}
			}
		}
	}
}

void Game::render()
{
	renderer->getWindow()->clear();
	renderer->drawBg(1);
	renderer->drawLongIntColor(score->getScore(), 450.0f, 69.0f, sf::Color::Black);
	renderer->drawLongIntColor(static_cast<long>(score->getLineCleared()), 426.0f, 237.0f, sf::Color::Black);
	renderer->drawLongIntColor(static_cast<long>(score->getLevel()), 426.0f, 165.0f, sf::Color::Black);
	renderer->drawPreview(rng.getNext());
	renderer->drawPoints(manager.getPiece()->getPieces());
	renderer->drawPoints(board.getPieces());
	renderer->getWindow()->display();
}

void Game::deactivate()
{
	timer.deleteTime(4);
	activated = false;
}

bool Game::isDeactivateCondition()
{
	if (gameOver and !gameOverFillAnimation and timer.isPassed(10))
	{
		timer.deleteTime(10);
		return true;
	}
	return false;
}


