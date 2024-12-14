# Stock Market Simulator

A stock market simulation program that provides a realistic trading environment for practice investment.

## Prerequisites

Required for program execution:

- GCC compiler
- C standard library
- Unix-based system (Linux/MacOS) or Windows

## Installation

1. Clone repository:
```bash
git clone [repository-url]
cd stock-simulator
```

2. Compile program:
```bash
gcc -I. -o stock_simulator main.c user_system.c stock_system.c portfolio_system.c
```

3. Initial data setup:
```bash
# Create trading_data directory
mkdir -p trading_data

# Create stocks.txt file and input initial data
cat > trading_data/stocks.txt << EOL
005930 삼성전자 전자 72000 0.0
035420 NAVER IT 220000 0.0
000660 SK하이닉스 반도체 130000 0.0
005380 현대차 자동차 185000 0.0
051910 LG화학 화학 580000 0.0
035720 카카오 IT 48000 0.0
006400 삼성SDI 전자 710000 0.0
207940 삼성바이오 바이오 820000 0.0
373220 LG에너지솔루션 전자 420000 0.0
000270 기아 자동차 82000 0.0
EOL
```

## Usage

1. Run program:
```bash
./stock_simulator
```

2. Core Features:
- Sign up/Login
- View stock listings
- Search stocks
- Buy/Sell stocks
- Portfolio management

3. Data Files:
- `trading_data/users.txt`: User information
- `trading_data/stocks.txt`: Stock information
- `trading_data/portfolio.txt`: Portfolio information
- `trading_data/transactions.txt`: Transaction history

## Inference

### Trading Process
1. After login, select "1. Stock List" from main menu
2. Enter the name of stock you want to trade
3. Choose buy/sell and enter quantity

### Transaction Record Format
```
사용자ID 종목코드 거래유형 수량 가격 날짜
Example: user1 005930 B 10 72000 2024-12-14
```
- Transaction type: B(Buy), S(Sell)

### Automatic Updates
- Stock prices automatically fluctuate between -5% and +5% every minute
- All transaction records and portfolio information are saved in real-time

## References

- C Language Express 4th Edition
- SW Convergence Coding 2 Course Materials

### Project Structure
```
stock_simulator/
├── main.c
├── user_system.c
├── user_system.h
├── stock_system.c
├── stock_system.h
├── portfolio_system.c
├── portfolio_system.h
└── trading_data/
    ├── users.txt
    ├── stocks.txt
    ├── portfolio.txt
    └── transactions.txt
```

### Developer Information
- SW융합대학 모바일시스템공학과 조민형
- SW융합대학 컴퓨터공학과 신철민
- SW융합대학 모바일시스템공학과 정승아
