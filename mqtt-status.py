import paho.mqtt.client as mqtt
import pygame

def on_message(client, userdata, msg):
    print(msg.payload)
    if (str(msg.payload) == "b'busy'"):
        print("I'm busy")
        screen.fill((255,0,0))
        pygame.display.flip()
    if (str(msg.payload) == "b'notBusy'"):
        print("Free")
        screen.fill((0,255,0))
        pygame.display.flip()


pygame.init()
screen = pygame.display.set_mode((0,0), pygame.FULLSCREEN)
pygame.mouse.set_visible(0)
screen.fill((0,255,0))
pygame.display.flip()


client = mqtt.Client()
client.on_message = on_message

client.connect("192.168.0.143", 1883, 60)
client.subscribe("inTopic",0)

running = True
while running:    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running= False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False
    client.loop()

pygame.quit()



