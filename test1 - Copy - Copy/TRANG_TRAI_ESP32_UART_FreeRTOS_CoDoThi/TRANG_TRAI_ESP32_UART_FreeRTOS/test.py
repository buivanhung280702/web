#import RPi.GPIO as GPIO
import telepot
from telepot.loop import MessageLoop

# Vô hiệu hóa cảnh báo
#GPIO.setwarnings(False)

# Thiết lập chân GPIO
##GPIO.setmode(GPIO.BOARD)
#GPIO.setup(12, GPIO.OUT)

# Hàm xử lý tin nhắn
def handle_message(msg):
    content_type, chat_type, chat_id = telepot.glance(msg)
    if content_type == 'text':
        command = msg['text']
        if command == 'onpk':
           # GPIO.output(12, GPIO.HIGH)  # Bật đèn
            print("on")
        elif command == 'offpk':
           # GPIO.output(12, GPIO.LOW)   # Tắt đèn
            print("off")

# Khởi tạo bot
bot = telepot.Bot('6835695986:AAGYlXlzH1lZpPrx0akSnjNi-vfvcxZGzNE')

# Lắng nghe tin nhắn từ bot và gọi hàm xử lý tin nhắn
MessageLoop(bot, handle_message).run_forever()

