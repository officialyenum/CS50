WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

PADDLE_SPEED = 200

Class = require 'class'
push = require 'push'

require 'Ball'
require 'Paddle'


function love.load()
    love.window.setTitle('Pong')
    love.graphics.setDefaultFilter('nearest', 'nearest')
    smallFont = love.graphics.newFont('font.ttf', 8)
    victoryFont = love.graphics.newFont('font.ttf', 24)
    scoreFont = love.graphics.newFont('font.ttf', 32)

    sounds = {
        ['paddle_hit'] = love.audio.newSource('paddle_hit.wav', 'static'),
        ['wall_hit'] = love.audio.newSource('wall_hit.wav', 'static'),
        ['score'] = love.audio.newSource('score.wav', 'static')
    }

    --  initialized window with virtual resolution
    push:setupScreen(VIRTUAL_WIDTH,VIRTUAL_HEIGHT,WINDOW_WIDTH,WINDOW_HEIGHT, {
        fullscreen = false,
        vsync = true,
        resizable = true
    })


    player1Score = 0
    player2Score = 0

    servingPlayer = math.random(2) == 1 and 1 or 2
    winningPlayer = 0

    
    ball = Ball(VIRTUAL_WIDTH / 2 - 2, VIRTUAL_HEIGHT / 2 - 2, 5, 5)

    paddle1 = Paddle(5,20,5,20)
    paddle2 = Paddle(VIRTUAL_WIDTH - 10, 20, 5, 20)

    if servingPlayer == 1 then
        ball.dx = 100
    else
        ball.dx = -100
    end

    gameState = 'start'
    ball:reset()
    
end

function love.resize(w, h)
    push:resize(w, h)
end

function love.update(dt)

    paddle1:update(dt)
    paddle2:update(dt)


    -- is player human (player 1)
    if love.keyboard.isDown('w') then
        paddle1.dy = -PADDLE_SPEED
    elseif love.keyboard.isDown('s') then
        paddle1.dy = PADDLE_SPEED
    else
        paddle1.dy = 0
    end 

    --[[ -- is player computer (player 1)
    -- get ball delta position y
    ballPosY = ball.dy
    -- if ball y is above paddle y move paddle y up
    if ballPosY > paddle1.y and ball:collides(paddle2) then
        paddle1.dy = -PADDLE_SPEED
    -- if ball y is below paddle y move paddle y down
    elseif ballPosY < paddle2.y and ball:collides(paddle2) then
        paddle1.dy = PADDLE_SPEED
    else
        paddle1.dy = ballPosY
    end ]]


    -- is player computer (player 2)
    -- get ball delta position y
    ballPosY = ball.dy
    -- if ball y is above paddle y move paddle y up
    if ballPosY > paddle2.y and ball:collides(paddle1) then
        paddle2.dy = -PADDLE_SPEED
    -- if ball y is below paddle y move paddle y down
    elseif ballPosY < paddle2.y and ball:collides(paddle1) then
        paddle2.dy = PADDLE_SPEED
    else
        paddle2.dy = ballPosY
    end


    -- is player human (player 2)
    --[[ if love.keyboard.isDown('up') then
        paddle2.dy = -PADDLE_SPEED
    elseif love.keyboard.isDown('down') then
        paddle2.dy = PADDLE_SPEED
    else
        paddle2.dy = 0
    end ]]

    if gameState == 'play' then

        if ball:collides(paddle1) then
            -- deflect ball to right
            ball.dx = -ball.dx
            sounds['paddle_hit']:play()
        end

        if ball:collides(paddle2) then
            --deflect ball to the left
            ball.dx = -ball.dx
            sounds['paddle_hit']:play()
        end

        if ball.y <= 0 then
            --deflect ball down
            ball.dy = -ball.dy
            ball.y = 0
            sounds['wall_hit']:play()
        end

        if ball.y >= VIRTUAL_HEIGHT - 4 then
            --deflect ball up
            ball.dy = -ball.dy
            ball.y = VIRTUAL_HEIGHT - 4
            sounds['wall_hit']:play()
        end

        if ball.x < 0 then
            player2Score = player2Score + 1
            sounds['score']:play()
            servingPlayer = 1
            ball:reset()
            ball.dx = 100
            if player2Score >= 3 then
                gameState = 'victory'
                winningPlayer = 2
            else
                gameState = 'serve'
            end
        end

        if ball.x > VIRTUAL_WIDTH - 4 then
            player1Score = player1Score + 1
            sounds['score']:play()
            servingPlayer = 2
            ball:reset()
            ball.dx = -100
            if player1Score >= 3 then
                gameState = 'victory'
                winningPlayer = 1
            else
                gameState = 'serve'
            end
        end

        ball:update(dt)
    end
end

function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    elseif key == 'enter' or key == 'return' then
        if gameState == 'start' then
            gameState = 'serve'
        elseif gameState == 'victory' then
            gameState = 'start'
            player1Score = 0
            player2Score = 0
        elseif gameState == 'serve' then
            gameState = 'play'
        end
    end
end

function love.draw()
    -- begin rendering at virtual resolution
    push:apply('start')

    -- clear the screen with a specific color: in this case, a color similar
    -- to some versions of the original Pong
    love.graphics.clear(40 / 255,45 / 255,52 / 255,255 / 255)
    
    -- render ball
    ball:render()
    -- render paddles
    paddle1:render()
    paddle2:render()

    -- display FPS
    displayFPS()


    -- draw different things based on the state of the game
    if gameState == 'start' then
        love.graphics.setFont(smallFont)
        love.graphics.printf(
            "Welcome to Pong!", 
            0, 
            10, 
            VIRTUAL_WIDTH, 
            'center'
        )
        love.graphics.printf(
            "Press Enter to Play!", 
            0, 
            42, 
            VIRTUAL_WIDTH, 
            'center'
        )
    elseif gameState == 'serve' then
        love.graphics.setFont(smallFont)
        love.graphics.printf(
            "Player " .. tostring(servingPlayer) .. "'s turn!", 
            0, 
            10, 
            VIRTUAL_WIDTH, 
            'center'
        )
        love.graphics.printf(
            "Press Enter to Serve!", 
            0, 
            42, 
            VIRTUAL_WIDTH, 
            'center'
        )
    elseif gameState == 'victory' then
        love.graphics.setFont(victoryFont)
        love.graphics.printf(
            "Player " .. tostring(winningPlayer) .. " WINS!", 
            0, 
            10, 
            VIRTUAL_WIDTH, 
            'center'
        )
        love.graphics.setFont(smallFont)
        love.graphics.printf(
            "Press Enter to Play another Match!", 
            0, 
            42, 
            VIRTUAL_WIDTH, 
            'center'
        )
    elseif gameState == 'play' then
    end
    love.graphics.setFont(scoreFont)
    love.graphics.print(
        player1Score, 
        VIRTUAL_WIDTH / 2 - 50,
        VIRTUAL_HEIGHT / 3
    )

    love.graphics.print(
        player2Score, 
        VIRTUAL_WIDTH / 2 + 30,
        VIRTUAL_HEIGHT / 3
    )

    push:apply('end')
end

function displayFPS()
    love.graphics.setColor(0,1,0,1)
    love.graphics.setFont(smallFont)
    love.graphics.print('FPS: ' .. tostring(love.timer.getFPS()), 40, 20)
    love.graphics.setColor(1,1,1,1)
end

