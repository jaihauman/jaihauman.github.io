hello here is code&nbsp;<html lang="en">

  <box>
  <head>
    <meta charset="UTF-8"></meta>
    <meta content="width=device-width, initial-scale=1.0" name="viewport"></meta>
    <title>Quiz Website</title>
    <style>
       

        .container {
            text-align: center;
            background-color: white;
            padding: 20px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            width: 480p;
            max-width: 480px;
            box-sizing: border-box;
            position: relative;
        }

        .timer {
            position: absolute;
            top: 10px;
            right: 10px;
            font-size: 18px;
            background-color: #f7f7f7;
            border: 1px solid #ddd;
            padding: 5px 10px;
            border-radius: 5px;
        }

        button {
            margin-top: 20px;
            padding: 10px 20px;
            border: none;
            background-color: #007bff;
            color: white;
            cursor: pointer;
            transition: background-color 0.3s, transform 0.3s;
        }

        button:hover {
            background-color: #0056b3;
            transform: translateY(-2px);
        }

        button:active {
            background-color: #003f8a;
            transform: translateY(0);
        }

        .score-box {
            background-color: #007bff;
            color: white;
            padding: 10px;
            border-radius: 5px;
            font-size: 18px;
            margin-top: 20px;
        }

        .correct-answer {
            background-color: lightgreen;
            padding: 5px;
            border-radius: 3px;
        }

        .wrong-answer {
            background-color: lightcoral;
            padding: 5px;
            border-radius: 3px;
        }

        .nav-buttons {
            display: flex;
            justify-content: space-between;
            margin-top: 20px;
        }

        .option-button {
            display: block;
            width: 100%;
            margin: 5px 0;
            padding: 10px;
            background-color: #f0f0f0;
            border: 1px solid #ddd;
            border-radius: 5px;
            color: black;
            cursor: pointer;
            transition: background-color 0.3s, transform 0.3s;
        }

        .option-button:hover {
            background-color: #e0e0e0;
            transform: translateY(-2px);
        }

        .option-button:active {
            background-color: #d0d0d0;
            transform: translateY(0);
        }

        .option-button.selected {
            background-color: #007bff;
            color: white;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Quiz</h1>
        <div id="quiz-container">
            <button id="start-btn" onclick="startQuiz()">Start Quiz</button>
        </div>
        <div class="timer" id="timer-container" style="display: none;">
            <p>Time left: <span id="timer">30</span> seconds</p>
        </div>
    </div>
    <script>
        const questions = [
            { question: "राजस्थान का राज्य पशु क्या है?", options: ["चिंकारा", "ऊंट", "बाघ", "हाथी"], answer: "ऊंट" },
            { question: "राजस्थान की सबसे लंबी नदी का नाम बताएं।", options: ["चंबल", "लूनी", "बनास", "माही"], answer: "चंबल" },
            { question: "राजस्थान का कौन सा शहर 'नीला शहर' के रूप में जाना जाता है?", options: ["जयपुर", "जैसलमेर", "जोधपुर", "उदयपुर"], answer: "जोधपुर" },
            { question: "राजस्थान की आधिकारिक भाषा क्या है?", options: ["हिंदी", "राजस्थानी", "मारवाड़ी", "पंजाबी"], answer: "हिंदी" },
            { question: "राजस्थान के पहले मुख्यमंत्री कौन थे?", options: ["हीरा लाल शास्त्री", "मोहन लाल सुखाड़िया", "जय नारायण व्यास", "भैरो सिंह शेखावत"], answer: "हीरा लाल शास्त्री" }
        ];

        let currentQuestionIndex = 0;
        let score = 0;
        let timer;
        let userAnswers = [];

        function startQuiz() {
            currentQuestionIndex = 0;
            score = 0;
            userAnswers = [];
            document.getElementById('start-btn').style.display = 'none';
            document.getElementById('timer-container').style.display = 'block';
            startTimer();
            loadQuestion();
        }

        function startTimer() {
            let timeLeft = 30;
            document.getElementById('timer').textContent = timeLeft;
            timer = setInterval(() => {
                timeLeft--;
                document.getElementById('timer').textContent = timeLeft;
                if (timeLeft <= 0) {
                    clearInterval(timer);
                    showResults();
                }
            }, 1000);
        }

        function loadQuestion() {
            const quizContainer = document.getElementById('quiz-container');
            const question = questions[currentQuestionIndex];
            quizContainer.innerHTML = `
                <h2>Question ${currentQuestionIndex + 1}: ${question.question}</h2>
                ${question.options.map(option => `
                    <button class="option-button ${userAnswers[currentQuestionIndex] === option ? 'selected' : ''}" onclick="selectOption('${option}')">${option}</button>
                `).join('')}
                <div class="nav-buttons">
                    <button onclick="previousQuestion()" ${currentQuestionIndex === 0 ? 'disabled' : ''}>Back</button>
                    <button onclick="nextQuestion()">Next</button>
                </div>
            `;
        }

        function selectOption(option) {
            userAnswers[currentQuestionIndex] = option;
            document.querySelectorAll('.option-button').forEach(button => {
                button.classList.remove('selected');
                if (button.textContent === option) {
                    button.classList.add('selected');
                }
            });
        }

        function nextQuestion() {
            if (userAnswers[currentQuestionIndex] === questions[currentQuestionIndex].answer) {
                score++;
            }
            currentQuestionIndex++;
            if (currentQuestionIndex < questions.length) {
                loadQuestion();
            } else {
                clearInterval(timer);
                showResults();
            }
        }

        function previousQuestion() {
            currentQuestionIndex--;
            loadQuestion();
        }

        function showResults() {
            const quizContainer = document.getElementById('quiz-container');
            document.getElementById('timer-container').style.display = 'none';
            let resultsHTML = `
                <h2>Quiz Completed!</h2>
                <div class="score-box">Your score: ${score} / ${questions.length}</div>
                <button onclick="showAnswers()">Show Answers</button>
                <div id="answers-container" style="display: none;">
                    <h3>Correct and Incorrect Answers:</h3>
            `;
            questions.forEach((question, index) => {
                const userAnswer = userAnswers[index];
                const isCorrect = userAnswer === question.answer;
                resultsHTML += `
                    <div>
                        <p><strong>Question ${index + 1}:</strong> ${question.question}</p>
                        <p><strong>Your answer:</strong> <span class="${isCorrect ? 'correct-answer' : 'wrong-answer'}">${userAnswer || "No answer selected"}</span></p>
                        <p><strong>Correct answer:</strong> ${question.answer}</p>
                    </div>
                    <hr>
                `;
            });
            resultsHTML += `<div class="score-box">Your final score: ${score} / ${questions.length}</div></div>`;
            resultsHTML += `<button onclick="restartQuiz()">Restart Quiz</button>`;
            quizContainer.innerHTML = resultsHTML;
        }

        function showAnswers() {
            document.getElementById('answers-container').style.display = 'block';
        }

        function restartQuiz() {
            document.getElementById('quiz-container').innerHTML = `
                <button id="start-btn" onclick="startQuiz()">Start Quiz</button>
            `;
        }
    </script>
</body>
</html>
 </box>
