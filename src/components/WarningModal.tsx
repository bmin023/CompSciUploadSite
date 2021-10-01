import {
  Alert,
  AlertIcon,
  Button,
  Modal,
  ModalBody,
  ModalCloseButton,
  ModalContent,
  ModalFooter,
  ModalHeader,
  ModalOverlay,
  VStack,
} from "@chakra-ui/react";
import React from "react";

interface WarningModalProps {
  warnings: string[];
  isOpen: boolean;
  onClose: () => void;
}

const WarningModal: React.FC<WarningModalProps> = ({
  warnings,
  isOpen,
  onClose,
}) => {
  return (
    <Modal onClose={onClose} isOpen={isOpen} scrollBehavior="outside">
      <ModalOverlay />
      <ModalContent>
        <ModalHeader>Warnings</ModalHeader>
        <ModalCloseButton />
        <ModalBody>
          <VStack>
            {warnings.map((warning) => {
              return (
                <Alert borderRadius="xl" status="warning">
                  <AlertIcon />
                  {warning}
                </Alert>
              );
            })}
          </VStack>
        </ModalBody>
        <ModalFooter>
          <Button onClick={onClose}>Close</Button>
        </ModalFooter>
      </ModalContent>
    </Modal>
  );
};

export default WarningModal;
