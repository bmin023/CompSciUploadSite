import { Box, Button } from "@chakra-ui/react";
import axios from "axios";
import { Form, Formik } from "formik";
import React from "react";

import InputField from "components/InputField";

const Login = () => {
  return (
    <Box mt={8} mx="auto" w="50%">
      <Formik
        initialValues={{ username: "", password: "" }}
        onSubmit={async (values, { setErrors }) => {
          const res = await axios.post("/api/register", {
            username: values.username,
            password: values.password,
          });
          const { data } = res;
          setErrors({
            username: data.username,
            password: data.password,
          });
        }}
      >
        {({ isSubmitting }) => (
          <Form>
            <InputField
              name="username"
              placeholder="Username"
              label="Username"
            />
            <Box mt={4}>
              <InputField
                name="password"
                placeholder="password"
                label="Password"
                type="password"
              />
            </Box>
            <Button
              type="submit"
              colorScheme="blue"
              mt={4}
              isLoading={isSubmitting}
            >
              Login
            </Button>
          </Form>
        )}
      </Formik>
    </Box>
  );
};

export default Login;
