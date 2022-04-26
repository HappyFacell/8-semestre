import nacl.secret
import nacl.utils

key = nacl.utils.random(nacl.secret.SecretBox.KEY_SIZE)

box = nacl.secret.SecretBox(key)

message = b"The president will be exiting through the lower levels"

encrypted = box.encrypt(message)

print(type(message))

print(type(encrypted))

desencrypt = box.decrypt(encrypted)

print(type(desencrypt))

# # This is a nonce, it *MUST* only be used once, but it is not considered
# #   secret and can be transmitted or stored alongside the ciphertext. A
# #   good source of nonces are just sequences of 24 random bytes.
# nonce = nacl.utils.random(nacl.secret.SecretBox.NONCE_SIZE)

# encrypted = box.encrypt(message, nonce)

# nonce = nacl.utils.random(nacl.secret.SecretBox.NONCE_SIZE)

# encrypted = box.encrypt(message, nonce)

# # since we are transmitting the nonce by some other means,
# # we just need to get the ciphertext and authentication data

# ctext = encrypted.ciphertext

# # ctext is just nacl.secret.SecretBox.MACBYTES longer
# # than the original message

# assert len(ctext) == len(message) + box.MACBYTES

# # Decrypt our message, an exception will be raised if the encryption was
# #   tampered with or there was otherwise an error.
# plaintext = box.decrypt(encrypted)
# print(plaintext.decode('utf-8'))