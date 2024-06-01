from telethon import TelegramClient, events
import logging

logging.basicConfig(level=logging.INFO)

api_id = '12767327'  # Thay thế với API ID của bạn
api_hash = 'ab5eac1570321b4e4106c83e5d4d0967'  # Thay thế với API Hash của bạn
bot_token = '7024971081:AAGEgec38iIOsFR7rtjJkhBCjJh99cqm1DA'

# Tạo một instance của TelegramClient
client = TelegramClient('bot', api_id, api_hash)

async def start_bot():
    await client.start(bot_token=bot_token)
    print("Bot đã được khởi động và kết nối thành công.")

@client.on(events.NewMessage)
async def echo(event):
    me = await client.get_me()
    logging.info(f"Đã nhận được tin nhắn từ {event.message.sender_id}")
    if event.message.sender_id == me.id:
        message_content = event.message.message
        logging.info(f"Nội dung tin nhắn: {message_content}")
        print(message_content)
    else:
        logging.info("Tin nhắn không phải từ bot, bỏ qua.")

def main():
    try:
        client.loop.run_until_complete(start_bot())
        print("Bot đang chạy...")
        client.run_until_disconnected()
    except Exception as e:
        logging.error(f"Đã xảy ra lỗi: {e}")

if __name__ == '__main__':
    main()