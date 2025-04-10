import heapq
from collections import defaultdict

class HuffmanNode:
    def __init__(self, char=None, freq=0, left=None, right=None):
        self.char = char  # Character (None for internal nodes)
        self.freq = freq  # Frequency
        self.left = left  # Left child
        self.right = right  # Right child

    # For heap comparison (nodes are sorted by frequency)
    def __lt__(self, other):
        return self.freq < other.freq

def build_frequency_table(text):
    freq = defaultdict(int)
    for char in text:
        freq[char] += 1
    return freq

def build_huffman_tree(freq):
    heap = []
    # Push all characters into the min-heap
    for char, count in freq.items():
        heapq.heappush(heap, HuffmanNode(char=char, freq=count))
    
    # Build the Huffman tree
    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        merged = HuffmanNode(freq=left.freq + right.freq, left=left, right=right)
        heapq.heappush(heap, merged)
    
    return heapq.heappop(heap)  # Root of the Huffman tree

def build_huffman_codes(root, current_code="", codes={}):
    if root is None:
        return
    
    # Leaf node: assign the code
    if root.char is not None:
        codes[root.char] = current_code
        return
    
    # Traverse left (append '0') and right (append '1')
    build_huffman_codes(root.left, current_code + "0", codes)
    build_huffman_codes(root.right, current_code + "1", codes)
    
    return codes

def huffman_encode(text):
    if not text:
        return "", {}
    
    freq = build_frequency_table(text)
    root = build_huffman_tree(freq)
    codes = build_huffman_codes(root)
    
    encoded_text = ''.join([codes[char] for char in text])
    return encoded_text, codes

def huffman_decode(encoded_text, codes):
    if not encoded_text:
        return ""
    
    # Reverse the code dictionary for decoding
    reverse_codes = {v: k for k, v in codes.items()}
    current_code = ""
    decoded_text = []
    
    for bit in encoded_text:
        current_code += bit
        if current_code in reverse_codes:
            decoded_text.append(reverse_codes[current_code])
            current_code = ""
    
    return ''.join(decoded_text)

# Example Usage
if __name__ == "__main__":
    #text = "abracadabra"
    text = "kakornian probando huffman"
    print(f"Original Text: {text}")
    
    # Encoding
    encoded_text, huffman_codes = huffman_encode(text)
    print(f"Encoded Text: {encoded_text}")
    print(f"Huffman Codes: {huffman_codes}")
    
    # Decoding
    decoded_text = huffman_decode(encoded_text, huffman_codes)
    print(f"Decoded Text: {decoded_text}")
    
